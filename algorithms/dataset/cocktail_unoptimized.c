#include <string.h>

/* Unoptimized baseline: cocktail shaker sort, O(n^2). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    int left = 0, right = n - 1, swapped = 1;
    while (left < right && swapped) {
        swapped = 0;
        for (int i = left; i < right; ++i) if (output[i] > output[i + 1]) {
            int t = output[i]; output[i] = output[i + 1]; output[i + 1] = t; swapped = 1;
        }
        --right;
        for (int i = right; i > left; --i) if (output[i - 1] > output[i]) {
            int t = output[i]; output[i] = output[i - 1]; output[i - 1] = t; swapped = 1;
        }
        ++left;
    }
}
