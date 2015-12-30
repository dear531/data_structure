#include <stdio.h>

static void merge(int *a, int *tmp, int start, int mid, int end)
{
	int i = start, j = mid + 1, k = start;
	while (i <= mid && j <= end) {
		if (a[i] <= a[j]) {
			tmp[k++] = a[i++];
		} else {
			tmp[k++] = a[j++];
		}
	}
	while (i <= mid) {
		tmp[k++] = a[i++];
	}
	while (j <= end) {
		tmp[k++] = a[j++];
	}
	for (i = start; i <= end; i++)
		a[i] = tmp[i];
	return;
}

static void merge_sort(int *a, int *tmp, int start, int end)
{
	if (start == end)
		return;
	int mid = (start + end) / 2;
	merge_sort(a, tmp, start, mid);
	merge_sort(a, tmp, mid + 1, end);
	merge(a, tmp, start, mid, end);
}

int main(void)
{
	int a[] = {10, 2, 4, 6, 8, 1, 3, 5, 7, 9};
	int b[sizeof(a) / sizeof(*a)];
	merge_sort(a, b, 0, sizeof(a) / sizeof(*a) - 1);
	int i;
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	}
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		fprintf(stdout, "b[%d]:%d\n", i, b[i]);
	}
	return 0;
}
