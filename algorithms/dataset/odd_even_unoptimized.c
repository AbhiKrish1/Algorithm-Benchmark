#include <string.h>

/* Unoptimized baseline: odd-even transposition sort, O(n^2). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    int changed = 1;
    while (changed) {
        changed = 0;
        for (int phase = 0; phase < 2; ++phase) {
            for (int i = phase; i + 1 < n; i += 2) {
                if (output[i] > output[i + 1]) {
                    int temp = output[i]; output[i] = output[i + 1]; output[i + 1] = temp;
                    changed = 1;
                }
            }
        }
    }
}
