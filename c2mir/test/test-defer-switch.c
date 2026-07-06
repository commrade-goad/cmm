// Test defer inside switch
#include <stdio.h>

int order[20];
int idx;

void record(int v) { order[idx++] = v; }

int main() {
    // Defer inside switch case with break
    {
        int x = 1;
        switch (x) {
            case 1: {
                defer { record(1); }
                record(2);
                break;
            }
            case 2:
                record(99);
                break;
        }
        record(3);
    }
    // Expected: 2, 1, 3
    if (order[0] != 2 || order[1] != 1 || order[2] != 3) {
        printf("FAIL: switch case defer wrong: %d %d %d (expected 2 1 3)\n", order[0], order[1], order[2]);
        return 1;
    }

    idx = 0;
    // Defer with return from switch case
    {
        int y = 0;
        switch (y) {
            case 0: {
                defer { record(10); }
                record(11);
                record(12);
                // fall through to end of switch, block-end defers run
                break;
            }
        }
    }
    // Expected: 11, 12, 10
    if (order[0] != 11 || order[1] != 12 || order[2] != 10) {
        printf("FAIL: switch fallthrough defer: %d %d %d (expected 11 12 10)\n", order[0], order[1], order[2]);
        return 1;
    }

    printf("PASS: switch with defers\n");
    return 0;
}
