#include <stdio.h>

static volatile int result_sink;

/* Optimized: binary search over the same implicit sorted array. O(log n). */
void algorithm(int n) {
    int target = n - 1;
    int low = 0;
    int high = n - 1;
    int found = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;
        if (mid == target) {
            found = mid;
            break;
        }
        if (mid < target) low = mid + 1;
        else high = mid - 1;
    }
    result_sink = found;
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) return 1;
    algorithm(n);
    return 0;
}
