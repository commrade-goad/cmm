#include ":c2m_stdlib.hmm"
#include <stdio.h>

int main() {
  /* array of ints */
  DynamicArray da = da_create(__type_of(int));
  printf("int array: size=%lu align=%lu kind=%d\n",
         (unsigned long)da.element_type.size,
         (unsigned long)da.element_type.align,
         (int)da.element_type.kind);

  int vals[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++)
    da_push(&da, vals[i]);

  printf("count=%d capacity=%d\n", da.count, da.capacity);
  for (int i = 0; i < da.count; i++) {
    Opaque *op = da_get(&da, i);
    printf("  [%d] = %d\n", i, *(int*)op.data);
  }

  da_destroy(&da);

  /* array of doubles */
  DynamicArray dad = da_create(__type_of(double));
  double dvals[] = {1.1, 2.2, 3.3};
  for (int i = 0; i < 3; i++)
    da_push(&dad, (Opaque){ &dvals[i], __type_of(double) });

  printf("\ndouble array: count=%d\n", dad.count);
  for (int i = 0; i < dad.count; i++) {
    Opaque *op = da_get(&dad, i);
    printf("  [%d] = %g\n", i, *(double*)op.data);
  }

  da_destroy(&dad);

  return 0;
}
