\begin{document}

#expand :prelude {
  #define NOB_IMPLEMENTATION
  #include "latex.h"
  #include "nob.h"
}

#expand :prelude {
  struct Foo {
    float bar;
  };
}
#expand :prelude {
  void figure(const char* path, const char* caption, const char* label, double width) {
      BLOCK("figure", "H") {
          ELM("centering");
          ELM("IfFileExists", path);

          GROUP { ELM("includegraphics", ATTR(TEXTWIDTH(width)), path); }

          GROUP {
              FRAMEBOX(ATTR(TEXTWIDTH(width))) GROUP {
                  ELM("rule", 0, ARG("0pt"), ARG("150pt"));
                  BOLD GROUP { printf("[Placeholder: %s]", path); }
              }
          }
          printf("\n");

          ELM("caption", caption);
          ELM("label", label);
      }
  }
}

The layout logic stays cleanly separated from standard markup text blocks.

#expand {
  struct Foo *foo = malloc(sizeof(struct Foo));
  foo.bar = 0.8;
  defer { if (foo) { free(foo); } }
  ELM("section", "Introduction");
  figure("assets/net.png", "Topologi Jaringan", "fig:net", foo.bar);
  Nob_Cmd cmd = {0};
  nob_cmd_append(&cmd, "echo", r#"hello "world""#);
  nob_cmd_run(&cmd);
}


