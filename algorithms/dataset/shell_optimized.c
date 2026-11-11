#include <string.h>

/* Optimized comparison: Shell sort with Ciura gaps; typically subquadratic. */
void algorithm(const int *input, int *output, int n) {
    static const int gaps[] = {701, 301, 132, 57, 23, 10, 4, 1};
    memcpy(output, input, (size_t)n * sizeof(*output));
    for (size_t g = 0; g < sizeof(gaps) / sizeof(gaps[0]); ++g) {
        int gap = gaps[g];
        if (gap >= n) continue;
        for (int i = gap; i < n; ++i) {
            int value = output[i];
            int j = i;
            while (j >= gap && output[j - gap] > value) {
                output[j] = output[j - gap];
                j -= gap;
            }
            output[j] = value;
        }
    }
}
