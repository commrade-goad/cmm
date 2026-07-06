// Test nested blocks with defer
#include <stdio.h>

int order[20];
int idx;

void record(int v) { order[idx++] = v; }

int main() {
    {
        defer { record(1); }
        {
            defer { record(2); }
            record(3);
        }
        record(4);
    }

    // Inner block exit: record(2), then outer: record(4), record(1)
    // Full sequence: 3, 2, 4, 1
    if (order[0] != 3 || order[1] != 2 || order[2] != 4 || order[3] != 1) {
        printf("FAIL: nested defers wrong: %d %d %d %d (expected 3 2 4 1)\n",
               order[0], order[1], order[2], order[3]);
        return 1;
    }
    printf("PASS: nested defers\n");
    return 0;
}
