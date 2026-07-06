// Test defer inside if/else branches
#include <stdio.h>

int order[10];
int idx;

void record(int v) { order[idx++] = v; }

int main() {
    // Defer in if branch only
    {
        if (1) {
            defer { record(1); }
            record(2);
        }
        record(3);
    }
    // Expected: 2, 1, 3
    if (order[0] != 2 || order[1] != 1 || order[2] != 3) {
        printf("FAIL: if defer wrong: %d %d %d (expected 2 1 3)\n", order[0], order[1], order[2]);
        return 1;
    }

    idx = 0;
    // Defer in else branch
    {
        if (0) {
            record(99);
        } else {
            defer { record(4); }
            record(5);
        }
        record(6);
    }
    // Expected: 5, 4, 6
    if (order[0] != 5 || order[1] != 4 || order[2] != 6) {
        printf("FAIL: else defer wrong: %d %d %d (expected 5 4 6)\n", order[0], order[1], order[2]);
        return 1;
    }

    printf("PASS: if/else with defers\n");
    return 0;
}
