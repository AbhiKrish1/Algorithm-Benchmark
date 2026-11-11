#include <string.h>

/* Unoptimized baseline: gnome sort, O(n^2). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    int i = 1;
    while (i < n) {
        if (i == 0 || output[i - 1] <= output[i]) ++i;
        else {
            int temp = output[i]; output[i] = output[i - 1]; output[i - 1] = temp;
            --i;
        }
    }
}
