#include <string.h>

/* Unoptimized baseline: selection sort, O(n^2). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    for (int i = 0; i < n - 1; ++i) {
        int min_index = i;
        for (int j = i + 1; j < n; ++j)
            if (output[j] < output[min_index]) min_index = j;
        int temp = output[i]; output[i] = output[min_index]; output[min_index] = temp;
    }
}
