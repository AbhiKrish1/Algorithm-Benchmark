#include <string.h>

static int median_of_three(int a, int b, int c) {
    if (a < b) return b < c ? b : (a < c ? c : a);
    return a < c ? a : (b < c ? c : b);
}

static void quick_sort(int *a, int low, int high) {
    while (low < high) {
        int pivot = median_of_three(a[low], a[low + (high - low) / 2], a[high]);
        int i = low - 1, j = high + 1;
        for (;;) {
            do { ++i; } while (a[i] < pivot);
            do { --j; } while (a[j] > pivot);
            if (i >= j) break;
            int temp = a[i]; a[i] = a[j]; a[j] = temp;
        }
        /* Recurse into the smaller partition to keep stack depth bounded. */
        if (j - low < high - (j + 1)) { quick_sort(a, low, j); low = j + 1; }
        else { quick_sort(a, j + 1, high); high = j; }
    }
}

/* Optimized comparison: median-of-three quicksort, average O(n log n). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    quick_sort(output, 0, n - 1);
}
