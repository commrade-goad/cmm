// Test __type_of struct field and enum member data
#include ":c2m_stdlib.hmm"
#include <stdio.h>

enum Color { RED = 10, GREEN = 20, BLUE = 30 };
struct Point { int x; int y; };
union Data { int i; double d; };

int main() {
    int pass = 1;

    /* --- enum member test --- */
    const __type_t *te = __type_of(enum Color);
    printf("Color: kind=%d members=%d\n", (int)te->kind, te->member_count);
    if (te->member_count != 3) { printf("  FAIL member_count\n"); pass = 0; }
    if (te->kind != __TYPE_ENUM) { printf("  FAIL kind\n"); pass = 0; }
    for (int i = 0; i < te->member_count && i < 64; i++) {
        printf("  [%d] %s = %d\n", i, te->member_names[i], (int)te->member_values[i]);
        if (i == 0 && te->member_values[i] != 10) { printf("  FAIL RED value\n"); pass = 0; }
        if (i == 1 && te->member_values[i] != 20) { printf("  FAIL GREEN value\n"); pass = 0; }
        if (i == 2 && te->member_values[i] != 30) { printf("  FAIL BLUE value\n"); pass = 0; }
    }

    /* --- struct field test --- */
    const __type_t *ts = __type_of(struct Point);
    printf("\nPoint: kind=%d fields=%d\n", (int)ts->kind, ts->field_count);
    if (ts->field_count != 2) { printf("  FAIL field_count\n"); pass = 0; }
    if (ts->kind != __TYPE_STRUCT) { printf("  FAIL kind\n"); pass = 0; }
    for (int i = 0; i < ts->field_count && i < 64; i++) {
        printf("  [%d] %s : %s (offset=%d)\n", i,
               ts->field_names[i], ts->field_types[i], (int)ts->field_offsets[i]);
    }

    /* --- union field test --- */
    const __type_t *tu = __type_of(union Data);
    printf("\nData: kind=%d fields=%d\n", (int)tu->kind, tu->field_count);
    if (tu->field_count != 2) { printf("  FAIL field_count\n"); pass = 0; }
    if (tu->kind != __TYPE_UNION) { printf("  FAIL kind\n"); pass = 0; }
    for (int i = 0; i < tu->field_count && i < 64; i++) {
        printf("  [%d] %s : %s (offset=%d)\n", i,
               tu->field_names[i], tu->field_types[i], (int)tu->field_offsets[i]);
    }

    /* --- primitive has no fields --- */
    const __type_t *ti = __type_of(int);
    if (ti->field_count != 0) { printf("  FAIL int field_count\n"); pass = 0; }
    if (ti->member_count != 0) { printf("  FAIL int member_count\n"); pass = 0; }

    printf("\n%s\n", pass ? "PASS" : "FAIL");
    return pass ? 0 : 1;
}
