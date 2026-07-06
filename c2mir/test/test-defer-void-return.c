// Test void function with defer and return
#include <stdio.h>

int order[20];
int idx;

void record(int v) { order[idx++] = v; }

void test_void_return(void) {
    defer { record(1); }
    record(2);
    return;
    record(99);
}

int main() {
    test_void_return();
    if (order[0] != 2 || order[1] != 1) {
        printf("FAIL: void return defers: %d %d (expected 2 1)\n", order[0], order[1]);
        return 1;
    }
    printf("PASS: void return with defers\n");
    return 0;
}
