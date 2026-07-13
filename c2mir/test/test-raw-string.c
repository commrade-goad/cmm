#include <stdio.h>
#include <string.h>

int main() {
    /* Multi-line raw string (was broken before fix) */
    const char *s = r#"
    Hello
    World
    "#;
    /* Content: "\n    Hello\n    World\n    " */
    if (strstr(s, "Hello") == NULL || strstr(s, "World") == NULL) {
        printf("FAIL: raw string content wrong: '%s'\n", s);
        return 1;
    }
    printf("PASS: multi-line raw string\n");
    return 0;
}
