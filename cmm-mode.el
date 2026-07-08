;;; cmm-mode.el --- major mode for editing cmm (c2mir fork) source -*- lexical-binding: t; -*-

;; Based on simpc-mode, reworked for the `cmm` language:
;; https://github.com/commrade-goad/cmm
;;
;; cmm is a fork of c2mir (from the MIR project) that keeps regular
;; C11 syntax but adds:
;;   - `defer`                  deferred statement, runs at scope exit
;;   - `__fresh__`               hygienic macro gensym
;;   - `__type_of`               runtime type-info descriptor (`__type_t *`)
;;   - `typeof`                  GNU-style typeof expression
;;   - auto-deref (`.` == `->` when the base is a pointer, no new keyword)
;;   - scoped `#define` / auto include guards (preprocessor behavior,
;;     no new keyword either)
;;
;; This mode drops the C++-only keyword set from the original
;; simpc-mode and keeps plain C89/C99/C11 keywords plus the cmm
;; extensions above.

(require 'subr-x)

(defvar cmm-mode-syntax-table
  (let ((table (make-syntax-table)))
    ;; C style comments
    (modify-syntax-entry ?/ ". 124b" table)
    (modify-syntax-entry ?* ". 23" table)
    (modify-syntax-entry ?\n "> b" table)
    ;; Preprocessor stuff?
    (modify-syntax-entry ?# "." table)
    ;; Chars are the same as strings
    (modify-syntax-entry ?' "\"" table)
    (modify-syntax-entry ?< "." table)
    (modify-syntax-entry ?> "." table)

    (modify-syntax-entry ?& "." table)
    (modify-syntax-entry ?% "." table)
    table))

(defun cmm-types ()
  '("char" "int" "long" "short" "void" "bool" "float" "double" "signed" "unsigned"
    "char16_t" "char32_t" "char8_t"
    "int8_t" "uint8_t" "int16_t" "uint16_t" "int32_t" "uint32_t" "int64_t" "uint64_t"
    "uintptr_t"
    "size_t" "ptrdiff_t"
    "va_list"
    ;; cmm runtime type-info descriptor (see TYPE_INFO.org)
    "__type_t"))

(defun cmm-keywords ()
  "Plain C89/C99/C11 keywords supported by c2mir (no C++)."
  '("auto" "break" "case" "const" "continue" "default" "do"
    "else" "enum" "extern" "for" "goto" "if" "inline" "register"
    "restrict" "return" "sizeof" "static" "struct" "switch" "typedef"
    "typeof" "union" "volatile" "while"
    ;; C11 underscore keywords
    "_Bool" "_Complex" "_Alignas" "_Alignof" "_Atomic" "_Generic"
    "_Noreturn" "_Static_assert" "_Thread_local"
    ;; stdbool.h / stdalign.h aliases commonly used
    "true" "false" "alignas" "alignof" "noreturn"))

(defun cmm-extension-keywords ()
  "Keywords that cmm adds on top of standard C (see README.md)."
  '("defer" "__fresh__" "__type_of"))

(defun cmm-constants ()
  "Runtime type-info enum constants from the `__type_t' reflection API."
  '("__TYPE_VOID" "__TYPE_BOOL" "__TYPE_CHAR" "__TYPE_SCHAR" "__TYPE_UCHAR"
    "__TYPE_SHORT" "__TYPE_USHORT" "__TYPE_INT" "__TYPE_UINT" "__TYPE_LONG"
    "__TYPE_ULONG" "__TYPE_LLONG" "__TYPE_ULLONG" "__TYPE_FLOAT" "__TYPE_DOUBLE"
    "__TYPE_LDOUBLE" "__TYPE_PTR" "__TYPE_ENUM" "__TYPE_STRUCT" "__TYPE_UNION"
    "__TYPE_ARRAY" "__TYPE_FUNC"))

(defun cmm-font-lock-keywords ()
  (list
   `("# *\\(warn\\|error\\)" . font-lock-warning-face)
   `("# *[#a-zA-Z0-9_]+" . font-lock-preprocessor-face)
   `("# *include\\(?:_next\\)?\\s-+\\(\\(<\\|\"\\).*\\(>\\|\"\\)\\)" . (1 font-lock-string-face))
   `(,(regexp-opt (cmm-constants) 'symbols) . font-lock-constant-face)
   `("\\(?:enum\\|struct\\|union\\)\\s-+\\([a-zA-Z0-9_]+\\)" . (1 font-lock-type-face))
   ;; highlight cmm-only extensions distinctly from plain C keywords
   `(,(regexp-opt (cmm-extension-keywords) 'symbols) . font-lock-builtin-face)
   `(,(regexp-opt (cmm-keywords) 'symbols) . font-lock-keyword-face)
   `(,(regexp-opt (cmm-types) 'symbols) . font-lock-type-face)))

(defun cmm--previous-non-empty-line ()
  "Returns either NIL when there is no such line or a pair (line . indentation)"
  (save-excursion
    ;; If you are on the first line, but not at the beginning of buffer (BOB) the `(bobp)`
    ;; function does not return `t`. So we have to move to the beginning of the line first.
    ;; TODO: feel free to suggest a better approach for checking BOB here.
    (move-beginning-of-line nil)
    (if (bobp)
        ;; If you are standing at the BOB, you by definition don't have a previous non-empty line.
        nil
      ;; Moving one line backwards because the current line is by definition is not
      ;; the previous non-empty line.
      (forward-line -1)
      ;; Keep moving backwards until we hit BOB or a non-empty line.
      (while (and (not (bobp))
                  (string-empty-p
                   (string-trim-right
                    (thing-at-point 'line t))))
        (forward-line -1))

      (if (string-empty-p
           (string-trim-right
            (thing-at-point 'line t)))
          ;; If after moving backwards for this long we still look at an empty
          ;; line we by definition didn't find the previous non-empty line.
          nil
        ;; We found the previous non-empty line!
        (cons (thing-at-point 'line t)
              (current-indentation))))))

(defun cmm--desired-indentation ()
  (let ((prev (cmm--previous-non-empty-line)))
    (if (not prev)
        (current-indentation)
      (let ((indent-len 4)
            (cur-line (string-trim-right (thing-at-point 'line t)))
            (prev-line (string-trim-right (car prev)))
            (prev-indent (cdr prev)))
        (cond
         ((string-match-p "^\\s-*switch\\s-*(.+)" prev-line)
          prev-indent)
         ((and (string-suffix-p "{" prev-line)
               (string-prefix-p "}" (string-trim-left cur-line)))
          prev-indent)
         ((string-suffix-p "{" prev-line)
          (+ prev-indent indent-len))
         ((string-prefix-p "}" (string-trim-left cur-line))
          (max (- prev-indent indent-len) 0))
         ((string-suffix-p ":" prev-line)
          (if (string-suffix-p ":" cur-line)
              prev-indent
            (+ prev-indent indent-len)))
         ((string-suffix-p ":" cur-line)
          (max (- prev-indent indent-len) 0))
         (t prev-indent))))))

;;; TODO: customizable indentation (amount of spaces, tabs, etc)
(defun cmm-indent-line ()
  (interactive)
  (when (not (bobp))
    (let* ((desired-indentation
            (cmm--desired-indentation))
           (n (max (- (current-column) (current-indentation)) 0)))
      (indent-line-to desired-indentation)
      (forward-char n))))

;;;###autoload
(define-derived-mode cmm-mode prog-mode "cmm"
  "Major mode for editing cmm (c2mir fork) source files."
  :syntax-table cmm-mode-syntax-table
  (setq-local font-lock-defaults '(cmm-font-lock-keywords))
  (setq-local indent-line-function 'cmm-indent-line)
  (setq-local comment-start "// "))

;;;###autoload
(add-to-list 'auto-mode-alist '("\\.cmm\\'" . cmm-mode))
;;;###autoload
(add-to-list 'auto-mode-alist '("\\.hmm\\'" . cmm-mode))

(provide 'cmm-mode)
;;; cmm-mode.el ends here
