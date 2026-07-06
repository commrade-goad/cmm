// Basic defer test: verify defers run in LIFO order at block exit
#include <stdio.h>

int main() {
    int order[10] = {0};
    int idx = 0;

    {
        defer { order[idx++] = 1; }
        defer { order[idx++] = 2; }
        defer { order[idx++] = 3; }
    }

    printf("Defer order: %d %d %d\n", order[0], order[1], order[2]);
    if (order[0] != 3 || order[1] != 2 || order[2] != 1) {
        printf("FAIL: expected 3 2 1\n");
        return 1;
    }
    printf("PASS\n");
    return 0;
}
