#include <stdio.h>

#define swap(t, a, b) { t __fresh__ = a; a = b; b = __fresh__; }

int main() {
    int tmp_ = 999;  // deliberately clash with naive naming
    int x = 1, y = 2;

    swap(int, x, y);

    if (x != 2 || y != 1) {
        printf("FAIL: swap failed\n");
        return 1;
    }
    if (tmp_ != 999) {
        printf("FAIL: outer tmp_ was clobbered (%d)\n", tmp_);
        return 1;
    }

    // Multiple expansions must get distinct names
    int a = 10, b = 20, c = 30, d = 40;
    swap(int, a, b);
    swap(int, c, d);
    if (a != 20 || b != 10 || c != 40 || d != 30) {
        printf("FAIL: multiple swaps failed\n");
        return 1;
    }

    printf("PASS\n");
    return 0;
}
