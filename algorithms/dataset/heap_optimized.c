#include <string.h>

static void sift_down(int *a, int root, int end) {
    while (root * 2 + 1 <= end) {
        int child = root * 2 + 1;
        if (child + 1 <= end && a[child] < a[child + 1]) ++child;
        if (a[root] >= a[child]) return;
        int temp = a[root]; a[root] = a[child]; a[child] = temp;
        root = child;
    }
}

/* Optimized comparison: in-place heap sort, O(n log n). */
void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    for (int start = n / 2 - 1; start >= 0; --start) sift_down(output, start, n - 1);
    for (int end = n - 1; end > 0; --end) {
        int temp = output[0]; output[0] = output[end]; output[end] = temp;
        sift_down(output, 0, end - 1);
    }
}
