#include ":c2m_stdlib.hmm"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct {
  void          *data;
  int            count;
  int            capacity;
  const __type_t *type;
} DynamicArray;

DynamicArray da_create(const __type_t *t) {
  DynamicArray da = {NULL, 0, 0, t};
  return da;
}

void da_destroy(DynamicArray *da) {
  free(da->data);
  da->data = NULL;
  da->count = 0;
  da->capacity = 0;
}

void da_push(DynamicArray *da, void *val) {
  if (da->count >= da->capacity) {
    int new_cap = da->capacity ? da->capacity * 2 : 4;
    void *new = realloc(da->data, (size_t)new_cap * da->type->size);
    da->data = new;
    da->capacity = new_cap;
  }
  memcpy((char*)da->data + da->count * da->type->size, val, da->type->size);
  da->count++;
}

void *da_get(DynamicArray *da, int i) {
  return (char*)da->data + i * da->type->size;
}

int main() {
  /* array of ints */
  DynamicArray da = da_create(__type_of(int));
  printf("int array: size=%lu align=%lu kind=%d\n",
         (unsigned long)da.type->size, (unsigned long)da.type->align, (int)da.type->kind);

  int vals[] = {10, 20, 30, 40, 50};
  for (int i = 0; i < 5; i++)
    da_push(&da, &vals[i]);

  printf("count=%d capacity=%d\n", da.count, da.capacity);
  for (int i = 0; i < da.count; i++)
    printf("  [%d] = %d\n", i, *(int*)da_get(&da, i));

  da_destroy(&da);

  /* array of doubles */
  DynamicArray dad = da_create(__type_of(double));
  double dvals[] = {1.1, 2.2, 3.3};
  for (int i = 0; i < 3; i++)
    da_push(&dad, &dvals[i]);

  printf("\ndouble array: count=%d\n", dad.count);
  for (int i = 0; i < dad.count; i++)
    printf("  [%d] = %g\n", i, *(double*)da_get(&dad, i));

  da_destroy(&dad);

  return 0;
}
