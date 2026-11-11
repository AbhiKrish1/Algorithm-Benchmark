#include <stdlib.h>
#include <string.h>

/* Optimized comparison: four-pass byte radix sort for nonnegative integers, O(n). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    int *scratch = malloc((size_t)n * sizeof(*scratch));
    if (!scratch) return;
    int *src = output, *dst = scratch;
    for (unsigned shift = 0; shift < sizeof(unsigned int) * 8; shift += 8) {
        size_t counts[256] = {0};
        for (int i = 0; i < n; ++i) ++counts[((unsigned)src[i] >> shift) & 255u];
        size_t offsets[256], total = 0;
        for (int b = 0; b < 256; ++b) { offsets[b] = total; total += counts[b]; }
        for (int i = 0; i < n; ++i) {
            unsigned bucket = ((unsigned)src[i] >> shift) & 255u;
            dst[offsets[bucket]++] = src[i];
        }
        int *temp = src; src = dst; dst = temp;
    }
    if (src != output) memcpy(output, src, (size_t)n * sizeof(*output));
    free(scratch);
}
