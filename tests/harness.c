/* Test harness: reads n then n ints from stdin, calls algorithm(), prints the sorted result. */
#include <stdio.h>
#include <stdlib.h>

void algorithm(const int *input, int *output, int n);

int main(void) {
    int n;
    if (scanf("%d", &n) != 1 || n < 0) return 2;
    int *in = malloc((size_t)(n > 0 ? n : 1) * sizeof(int));
    int *out = malloc((size_t)(n > 0 ? n : 1) * sizeof(int));
    if (!in || !out) return 3;
    for (int i = 0; i < n; ++i)
        if (scanf("%d", &in[i]) != 1) return 4;
    algorithm(in, out, n);
    for (int i = 0; i < n; ++i) printf("%d\n", out[i]);
    free(in); free(out);
    return 0;
}