#include <stdio.h>
#include <string.h>

int main (void) {
  const char *basic = r"C:\tmp\new\nline.txt";
  const char *quoted = r#"say "hello\nworld""#;
  const char *multi = r##"json: { "path": "C:\tmp\foo", "tag": "#raw" }"##;
  const char *mix = "pre:" r"\n" ":post";

  printf ("%s\n%s\n%s\n%s\n", basic, quoted, multi, mix);
  printf ("%d %d %d\n", strcmp (basic, "C:\\tmp\\new\\nline.txt") == 0,
          strcmp (mix, "pre:\\n:post") == 0, strstr (multi, "\"#raw\"") != NULL);
  return 0;
}
