// Test LIFO defer execution and basic functionality
#include <stdio.h>

int main() {
    int order[10] = {0};
    int idx = 0;

    {
        defer { order[idx++] = 1; }
        defer { order[idx++] = 2; }
        defer { order[idx++] = 3; }
    }

    if (order[0] != 3 || order[1] != 2 || order[2] != 1) {
        printf("FAIL: LIFO order wrong: %d %d %d (expected 3 2 1)\n", order[0], order[1], order[2]);
        return 1;
    }
    printf("PASS: LIFO order correct\n");
    return 0;
}
