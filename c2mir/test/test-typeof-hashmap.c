// Test HashMap from c2m_stdlib.hmm
#include ":c2m_stdlib.hmm"
#include <stdio.h>

int main() {
    int pass = 1;

    /* --- insert and lookup int→double --- */
    HashMap hm = hm_create(__type_of(int), __type_of(double));

    int keys[] = {42, 17, 99, 256, -3, 0, 1, 2, 3, 4};
    double vals[] = {3.14, 2.71, 1.61, 0.0, -1.5, 10, 20, 30, 40, 50};
    int n = sizeof(keys) / sizeof(keys[0]);

    for (int i = 0; i < n; i++)
        hm_set(&hm, opaque(keys[i]), opaque(vals[i]));

    printf("count=%d capacity=%d\n", hm.count, hm.capacity);
    if (hm.count != n) { printf("FAIL: wrong count\n"); pass = 0; }

    for (int i = 0; i < n; i++) {
        double *v = hm_get(&hm, opaque(keys[i]));
        if (v == NULL) { printf("FAIL: key %d not found\n", keys[i]); pass = 0; }
        else if (*v != vals[i]) { printf("FAIL: key %d expected %g got %g\n", keys[i], vals[i], *v); pass = 0; }
        else printf("  %d -> %g\n", keys[i], *v);
    }

    /* --- update --- */
    double upd = 999.0;
    hm_set(&hm, opaque(keys[0]), opaque(upd));
    double *v = hm_get(&hm, opaque(keys[0]));
    if (*v != 999.0) { printf("FAIL: update\n"); pass = 0; }
    else printf("\n  updated %d -> %g\n", keys[0], *v);

    /* --- missing key --- */
    int missing = 888;
    if (hm_has(&hm, opaque(missing))) { printf("FAIL: false positive\n"); pass = 0; }
    printf("  missing %d -> %s\n", missing, hm_get(&hm, opaque(missing)) == NULL ? "NULL" : "FOUND");

    /* --- remove --- */
    hm_remove(&hm, opaque(keys[1]));
    if (hm_has(&hm, opaque(keys[1]))) { printf("FAIL: remove didn't work\n"); pass = 0; }
    printf("  after remove %d: has=%s count=%d\n", keys[1],
           hm_has(&hm, opaque(keys[1])) ? "yes" : "no", hm.count);

    /* --- stress: force resize --- */
    for (int i = 100; i < 200; i++) {
        int k = i;
        double vv = (double) i;
        hm_set(&hm, opaque(k), opaque(vv));
    }
    printf("\n  after stress: count=%d capacity=%d\n", hm.count, hm.capacity);
    for (int i = 100; i < 110; i++) {
        double *vv = hm_get(&hm, opaque(i));
        if (vv == NULL || *vv != (double)i)
            { printf("FAIL: stress %d\n", i); pass = 0; }
    }
    /* check survivors from before resize */
    v = hm_get(&hm, opaque(keys[0]));
    if (v == NULL || *v != 999.0) { printf("FAIL: key survived\n"); pass = 0; }

    hm_destroy(&hm);

    printf("\n%s\n", pass ? "PASS" : "FAIL");
    return pass ? 0 : 1;
}
