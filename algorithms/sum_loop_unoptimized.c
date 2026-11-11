#include <stdio.h>

static volatile long long result_sink;

/* Unoptimized: adds every integer from 1 through n. O(n). */
void algorithm(int n) {
    long long sum = 0;
    for (int i = 1; i <= n; ++i) {
        sum += i;
    }
    result_sink = sum;
}

int main(void) {
    int n = 0;
    if (scanf("%d", &n) != 1) return 1;
    algorithm(n);
    return 0;
}
