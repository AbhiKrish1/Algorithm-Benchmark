#include <string.h>

/* Unoptimized baseline: bubble sort, O(n^2). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    for (int end = n - 1; end > 0; --end) {
        for (int i = 0; i < end; ++i) {
            if (output[i] > output[i + 1]) {
                int temp = output[i];
                output[i] = output[i + 1];
                output[i + 1] = temp;
            }
        }
    }
}
