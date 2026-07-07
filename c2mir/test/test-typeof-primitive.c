// Test __type_of with primitive types
#include ":c2m_stdlib.hmm"
#include <stdio.h>

int main() {
    int pass = 1;

    const __type_t *t;

    t = __type_of(void);
    printf("void:   name=%-8s size=%lu align=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (unsigned long)t->align, (int)t->kind);
    if (t->kind != __TYPE_VOID)  { printf("  FAIL kind\n");  pass = 0; }

    t = __type_of(int);
    printf("int:    name=%-8s size=%lu align=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (unsigned long)t->align, (int)t->kind);
    if (t->kind != __TYPE_INT)   { printf("  FAIL kind\n");  pass = 0; }
    if (t->size != sizeof(int))  { printf("  FAIL size\n");  pass = 0; }

    t = __type_of(char);
    printf("char:   name=%-8s size=%lu align=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (unsigned long)t->align, (int)t->kind);
    if (t->kind != __TYPE_CHAR)  { printf("  FAIL kind\n");  pass = 0; }
    if (t->size != 1)            { printf("  FAIL size\n");  pass = 0; }

    t = __type_of(double);
    printf("double: name=%-8s size=%lu align=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (unsigned long)t->align, (int)t->kind);
    if (t->kind != __TYPE_DOUBLE){ printf("  FAIL kind\n");  pass = 0; }

    t = __type_of(int*);
    printf("int*:   name=%-8s size=%lu align=%lu kind=%d\n",
           t->name, (unsigned long)t->size, (unsigned long)t->align, (int)t->kind);
    if (t->kind != __TYPE_PTR)   { printf("  FAIL kind\n");  pass = 0; }

    if (pass) printf("PASS\n");
    return pass ? 0 : 1;
}
