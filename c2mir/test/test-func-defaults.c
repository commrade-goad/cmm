#include <stdio.h>

int global_default_src = 42;

/* --- Default values --- */
int add(int a, int b = 10) {
    return a + b;
}

int mul(int a, int b = 2, int c = 3) {
    return a * b * c;
}

/* --- Default expression can refer to globals --- */
int with_global(int x = global_default_src) {
    return x;
}

/* --- Keyword arguments --- */
int divide(int dividend, int divisor = 1) {
    return dividend / divisor;
}

int main() {
    /* Default values */
    if (add(5) != 15) { printf("FAIL: add(5) = %d\n", add(5)); return 1; }
    if (add(5, 20) != 25) { printf("FAIL: add(5, 20) = %d\n", add(5, 20)); return 1; }

    if (mul(2) != 12) { printf("FAIL: mul(2) = %d\n", mul(2)); return 1; }
    if (mul(2, 4) != 24) { printf("FAIL: mul(2, 4) = %d\n", mul(2, 4)); return 1; }
    if (mul(2, 4, 5) != 40) { printf("FAIL: mul(2, 4, 5) = %d\n", mul(2, 4, 5)); return 1; }

    /* Keyword arguments */
    if (divide(.divisor = 5, .dividend = 30) != 6) {
        printf("FAIL: divide(.divisor=5, .dividend=30) = %d\n", divide(.divisor = 5, .dividend = 30));
        return 1;
    }

    /* Mixed positional + keyword */
    if (divide(30, .divisor = 6) != 5) {
        printf("FAIL: divide(30, .divisor=6) = %d\n", divide(30, .divisor = 6));
        return 1;
    }

    /* Keyword with default filling */
    if (divide(.dividend = 100) != 100) {
        printf("FAIL: divide(.dividend=100) = %d\n", divide(.dividend = 100));
        return 1;
    }

    /* Default from global */
    if (with_global() != 42) { printf("FAIL: with_global() = %d\n", with_global()); return 1; }
    if (with_global(99) != 99) { printf("FAIL: with_global(99) = %d\n", with_global(99)); return 1; }

    printf("ALL PASS\n");
    return 0;
}
