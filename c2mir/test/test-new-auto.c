#include <stdio.h>

typedef struct {
    int x,y;
} Point;

int main() {
    p := (Point) {10, 20};
    i := 20;
    f := 2.0;
    s := "hello world";

    for i := 0;
        i < 20;
        i++;
    {
        printf("hello %d\n", i);
    }
    return 0;
}
