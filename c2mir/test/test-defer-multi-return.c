// Test multiple return paths with defer
#include <stdio.h>

int order[20];
int idx;

void record(int v) { order[idx++] = v; }

int test_early_return(int cond) {
    defer { record(1); }
    if (cond) {
        record(2);
        return 10;
    }
    record(3);
    return 20;
}

int main() {
    // Test early return path
    int r1 = test_early_return(1);
    if (order[0] != 2 || order[1] != 1) {
        printf("FAIL: early return defers: %d %d (expected 2 1)\n", order[0], order[1]);
        return 1;
    }
    if (r1 != 10) {
        printf("FAIL: early return value: %d (expected 10)\n", r1);
        return 1;
    }
    printf("PASS: early return\n");

    idx = 0;
    // Test normal return path
    int r2 = test_early_return(0);
    if (order[0] != 3 || order[1] != 1) {
        printf("FAIL: normal return defers: %d %d (expected 3 1)\n", order[0], order[1]);
        return 1;
    }
    if (r2 != 20) {
        printf("FAIL: normal return value: %d (expected 20)\n", r2);
        return 1;
    }
    printf("PASS: normal return\n");

    printf("PASS: multi-return defers\n");
    return 0;
}
