// Test String and StringView from c2m_stdlib.hmm
#include ":c2m_stdlib.hmm"
#include <stdio.h>

int main() {
    int pass = 1;

    /* --- String build --- */
    String s = str_new();
    str_append(&s, "Hello");
    str_append_char(&s, ',');
    str_append(&s, " World!");
    if (s.count != 13) { printf("FAIL count\n"); pass = 0; }
    printf("str: '%s' (len=%d cap=%d)\n", str_cstr(&s), s.count, s.capacity);

    /* --- String from C string --- */
    String s2 = str_from("direct init");
    if (s2.count != 11) { printf("FAIL from count\n"); pass = 0; }
    printf("s2: '%s' (len=%d)\n", str_cstr(&s2), s2.count);

    /* --- String clear --- */
    str_clear(&s);
    if (s.count != 0) { printf("FAIL clear\n"); pass = 0; }
    printf("cleared: '%s' (len=%d)\n", str_cstr(&s), s.count);

    /* --- String re-use after clear --- */
    str_append(&s, "reuse");
    if (s.count != 5) { printf("FAIL reuse\n"); pass = 0; }
    printf("reuse: '%s' (len=%d)\n", str_cstr(&s), s.count);

    str_destroy(&s);
    str_destroy(&s2);

    /* --- StringView --- */
    StringView sv = sv_from("hello world");
    if (sv.count != 11) { printf("FAIL sv count\n"); pass = 0; }
    printf("sv: '%.*s' (len=%d)\n", sv.count, sv.data, sv.count);

    StringView sv2 = sv_from_parts("test data", 4);
    printf("sv2: '%.*s'\n", sv2.count, sv2.data);

    if (!sv_eq(sv2, sv_from("test"))) { printf("FAIL sv_eq\n"); pass = 0; }
    if (sv_eq(sv2, sv_from("data"))) { printf("FAIL sv_eq neg\n"); pass = 0; }

    if (!sv_starts_with(sv, "hello")) { printf("FAIL sv_starts_with\n"); pass = 0; }
    if (sv_starts_with(sv, "world")) { printf("FAIL sv_starts_with neg\n"); pass = 0; }

    if (!sv_ends_with(sv, "world")) { printf("FAIL sv_ends_with\n"); pass = 0; }
    if (sv_ends_with(sv, "hello")) { printf("FAIL sv_ends_with neg\n"); pass = 0; }

    printf("\n%s\n", pass ? "PASS" : "FAIL");
    return pass ? 0 : 1;
}
