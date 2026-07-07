// Test __type_of with struct, enum, union types
#include ":c2m_stdlib.hmm"
#include <stdio.h>

enum Color { RED, GREEN, BLUE };
struct Point { int x; int y; };
union Data { int i; double d; };
typedef struct { char a; int b; } Named;

int main() {
    int pass = 1;
    const __type_t *t;

    t = __type_of(enum Color);
    printf("Color: name=%s size=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (int)t->kind);
    if (t->kind != __TYPE_ENUM)  { printf("  FAIL kind\n");  pass = 0; }

    t = __type_of(struct Point);
    printf("Point: name=%s size=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (int)t->kind);
    if (t->kind != __TYPE_STRUCT){ printf("  FAIL kind\n");  pass = 0; }

    t = __type_of(union Data);
    printf("Data:  name=%s size=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (int)t->kind);
    if (t->kind != __TYPE_UNION) { printf("  FAIL kind\n");  pass = 0; }

    t = __type_of(Named);
    printf("Named: name=%s size=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (int)t->kind);
    if (t->kind != __TYPE_STRUCT){ printf("  FAIL kind\n");  pass = 0; }

    /* test expression form */
    struct Point pt = {1, 2};
    t = __type_of(pt);
    printf("pt:    name=%s size=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (int)t->kind);
    if (t->kind != __TYPE_STRUCT){ printf("  FAIL kind\n");  pass = 0; }

    if (pass) printf("PASS\n");
    return pass ? 0 : 1;
}
