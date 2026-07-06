// Test defer inside loops (for/while/do-while)
#include <stdio.h>

int order[20];
int idx;

void record(int v) { order[idx++] = v; }

int main() {
    // Defer inside for loop
    for (int i = 0; i < 3; i++) {
        defer { record(i); }
        record(i + 10);
    }
    // Each iteration: record(i+10), then block-end defer record(i)
    // i=0: 10, 0; i=1: 11, 1; i=2: 12, 2
    // Expected: 10, 0, 11, 1, 12, 2
    if (order[0] != 10 || order[1] != 0 || order[2] != 11 || order[3] != 1 || order[4] != 12 || order[5] != 2) {
        printf("FAIL: for loop defers wrong\n");
        return 1;
    }

    idx = 0;
    // Defer inside while loop
    // NOTE: defer captures `j` by reference, so when defer runs at block-end,
    // j has already been incremented by j++
    int j = 0;
    while (j < 2) {
        int saved = j;
        defer { record(saved + 20); }
        record(j + 30);
        j++;
    }
    if (order[0] != 30 || order[1] != 20 || order[2] != 31 || order[3] != 21) {
        printf("FAIL: while loop defers wrong\n");
        return 1;
    }

    printf("PASS: loop defers\n");
    return 0;
}
