#include <stdio.h>

/* Multiple labeled temps in one macro — same label → same var, different → different */
#define do_something(a, b) { \
    int __fresh__(c) = (a);  \
    int __fresh__(d) = (b);  \
    __fresh__(c) += __fresh__(d); \
    a = __fresh__(c); \
}

/* Mix of bare __fresh__ and labeled */
#define swap_bare_and_labeled(t, a, b) { \
    t __fresh__ = (a); \
    t __fresh__(tmp) = (b); \
    a = __fresh__(tmp); \
    b = __fresh__; \
}

int main() {
    int x = 10, y = 20;
    do_something(x, y);

    if (x != 30 || y != 20) {
        printf("FAIL: do_something x=%d y=%d (expected 30, 20)\n", x, y);
        return 1;
    }
    printf("PASS: do_something\n");

    // Multiple expansions — each expansion has fresh seqs
    int a = 1, b = 2, c = 3, d = 4;
    do_something(a, b);
    do_something(c, d);

    if (a != 3 || b != 2 || c != 7 || d != 4) {
        printf("FAIL: multiple do_something calls a=%d b=%d c=%d d=%d\n", a, b, c, d);
        return 1;
    }
    printf("PASS: multiple do_something calls\n");

    // swap with both bare and labeled fresh
    int p = 100, q = 200;
    swap_bare_and_labeled(int, p, q);
    if (p != 200 || q != 100) {
        printf("FAIL: swap_bare_and_labeled p=%d q=%d\n", p, q);
        return 1;
    }
    printf("PASS: swap_bare_and_labeled\n");

    printf("ALL PASS\n");
    return 0;
}
