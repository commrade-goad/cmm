#include <stdio.h>

/* --- Bulletproof Strict C11 Macro Overloading --- */
#define ELM_COUNT_HELP(_1, _2, _3, _4, N, ...) N
#define ELM_COUNT_ARGS(...) ELM_COUNT_HELP(__VA_ARGS__, 4, 3, 2, 1, dummy)

/* FIX 1: Evaluate the counter first before pasting the tokens! */
#define ELM_GLUE(a, b) a ## b
#define ELM_GLUE_EVAL(a, b) ELM_GLUE(a, b)
#define ELM_DISPATCH(N) ELM_GLUE_EVAL(ELM_, N)

#define ELM(...) ELM_DISPATCH(ELM_COUNT_ARGS(__VA_ARGS__))(__VA_ARGS__)

#define ELM_1(tag)                  do { printf("\\%s\n", tag); } while(0)
#define ELM_2(tag, content)         do { printf("\\%s{%s}\n", tag, content); } while(0)
#define ELM_3(tag, opt, content)    do { printf("\\%s[", tag); opt; printf("]{%s}\n", content); } while(0)
#define ELM_4(tag, opt, arg1, arg2) do { printf("\\%s[", tag); opt; printf("]"); arg1; arg2; printf("\n"); } while(0)

#define ARG(content)                do { printf("{%s}", content); } while(0)

/* FIX 2: ATTR must be a raw expression to safely sit inside FRAMEBOX */
#define ATTR(expr)                  expr

#define TEXTWIDTH(fraction)         printf("width=%.2f\\textwidth", (double)(fraction))
#define PT(points)                  printf("%.2fpt", (double)(points))

/* --- Structural Scoping Blocks --- */
#define BLOCK(tag, options) \
    for (int _i = (printf("\\begin{%s}[%s]\n", tag, options), 0); _i < 1; _i++, printf("\\end{%s}\n", tag))

#define GROUP \
    for (int _j = (printf("{"), 0); _j < 1; _j++, printf("}"))

#define FRAMEBOX(opt) \
    for (int _k = (printf("\\framebox["), (opt), printf("]"), 0); _k < 1; _k++)

#define BOLD \
    for (int _l = (printf("\\textbf"), 0); _l < 1; _l++)
