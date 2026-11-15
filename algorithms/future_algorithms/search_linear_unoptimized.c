#include <stdio.h>

static volatile int result_sink;

/* Unoptimized: scans each position until it finds n - 1. O(n). */
void algorithm(int n) {
    int target = n - 1;
    int found = -1;
    for (int i = 0; i < n; ++i) {
        /* The sorted test data is the implicit array [0, 1, ..., n - 1]. */
        if (i == target) {
            found = i;
            break;
        }
    }
    result_sink = found;
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) return 1;
    algorithm(n);
    return 0;
}
