// Test defer with return (defers run before return)
#include <stdio.h>

int order[10];
int idx;

void record(int v) { order[idx++] = v; }

int test_return() {
    defer { record(1); }
    defer { record(2); }
    record(3);
    return 42;
}

int main() {
    int ret = test_return();
    // order should be: 3, 2, 1 (stmt runs first, then defers LIFO)
    if (order[0] != 3 || order[1] != 2 || order[2] != 1) {
        printf("FAIL: return defers wrong: %d %d %d (expected 3 2 1)\n", order[0], order[1], order[2]);
        return 1;
    }
    if (ret != 42) {
        printf("FAIL: return value wrong: %d (expected 42)\n", ret);
        return 1;
    }
    printf("PASS: return with defers\n");
    return 0;
}
