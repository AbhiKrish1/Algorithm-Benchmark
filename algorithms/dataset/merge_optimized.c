#include <stdlib.h>
#include <string.h>

static void merge(int *values, int *scratch, int left, int middle, int right) {
    int i = left, j = middle, out = left;
    while (i < middle && j < right)
        scratch[out++] = values[i] <= values[j] ? values[i++] : values[j++];
    while (i < middle) scratch[out++] = values[i++];
    while (j < right) scratch[out++] = values[j++];
    for (i = left; i < right; ++i) values[i] = scratch[i];
}

static void merge_sort(int *values, int *scratch, int left, int right) {
    if (right - left < 2) return;
    int middle = left + (right - left) / 2;
    merge_sort(values, scratch, left, middle);
    merge_sort(values, scratch, middle, right);
    merge(values, scratch, left, middle, right);
}

/* Optimized comparison: merge sort, O(n log n). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    int *scratch = malloc((size_t)n * sizeof(*scratch));
    if (!scratch) return;
    merge_sort(output, scratch, 0, n);
    free(scratch);
}
