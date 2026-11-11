#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

void algorithm(const int *input, int *output, int n);

int main(void) {
    int n = 0, repeats = 0;
    if (scanf("%d %d", &n, &repeats) != 2 || n < 1 || repeats < 1) return 2;
    int *input = malloc((size_t)n * sizeof(*input));
    int *output = malloc((size_t)n * sizeof(*output));
    if (!input || !output) { free(input); free(output); return 3; }
    for (int i = 0; i < n; ++i) {
        if (scanf("%d", &input[i]) != 1) { free(input); free(output); return 4; }
    }

    clock_t start = clock();
    if (start == (clock_t)-1) { free(input); free(output); return 5; }
    for (int r = 0; r < repeats; ++r) algorithm(input, output, n);
    clock_t stop = clock();
    if (stop == (clock_t)-1) { free(input); free(output); return 5; }

    for (int i = 1; i < n; ++i) {
        if (output[i - 1] > output[i]) { free(input); free(output); return 6; }
    }
    printf("%.12g\n", ((double)(stop - start) / CLOCKS_PER_SEC) / repeats);
    free(input);
    free(output);
    return 0;
}
