#include <string.h>

/* Unoptimized baseline: insertion sort with a linear scan, O(n^2). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    for (int i = 1; i < n; ++i) {
        int value = output[i], j = i;
        while (j > 0 && output[j - 1] > value) {
            output[j] = output[j - 1];
            --j;
        }
        output[j] = value;
    }
}
