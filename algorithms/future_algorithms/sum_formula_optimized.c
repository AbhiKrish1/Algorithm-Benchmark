#include <stdio.h>

static volatile long long result_sink;

/* Optimized: uses the arithmetic-series formula. O(1). */
void algorithm(int n) {
    long long value = n;
    result_sink = value * (value + 1) / 2;
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) return 1;
    algorithm(n);
    return 0;
}
