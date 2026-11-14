#include <stdlib.h>
#include <string.h>

#define CUTOFF 16   /* below this size, insertion sort beats recursion */

static void insertion_sort(int *values, int left, int right) {
    for (int i = left + 1; i < right; ++i) {
        int key = values[i], j = i - 1;
        while (j >= left && values[j] > key) { values[j + 1] = values[j]; --j; }
        values[j + 1] = key;
    }
}

static void merge(const int *src, int *dst, int left, int middle, int right) {
    int i = left, j = middle, out = left;
    while (i < middle && j < right)
        dst[out++] = src[i] <= src[j] ? src[i++] : src[j++];
    while (i < middle) dst[out++] = src[i++];
    while (j < right) dst[out++] = src[j++];
}

/* Sorts src[left,right) and leaves the result in src; buf is scratch.
   Alternates the roles of the two arrays so no copy-back loop is needed. */
static void sort_into(int *src, int *buf, int left, int right);

static void sort_to_buf(int *src, int *buf, int left, int right) {
    /* Result must end up in buf. */
    if (right - left <= CUTOFF) {
        insertion_sort(src, left, right);
        memcpy(buf + left, src + left, (size_t)(right - left) * sizeof(int));
        return;
    }
    int middle = left + (right - left) / 2;
    sort_into(src, buf, left, middle);
    sort_into(src, buf, middle, right);
    merge(src, buf, left, middle, right);
}

static void sort_into(int *src, int *buf, int left, int right) {
    /* Result must end up in src. */
    if (right - left <= CUTOFF) { insertion_sort(src, left, right); return; }
    int middle = left + (right - left) / 2;
    sort_to_buf(src, buf, left, middle);
    sort_to_buf(src, buf, middle, right);
    merge(buf, src, left, middle, right);
}

void algorithm(const int *input, int *output, int n) {
    memcpy(output, input, (size_t)n * sizeof(*output));
    int *scratch = malloc((size_t)n * sizeof(*scratch));
    if (!scratch) return;
    sort_into(output, scratch, 0, n);
    free(scratch);
}