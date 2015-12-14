#include <stdio.h>

int merge(int *a, int low, int mid, int high)
{
	int tmp[high - low + 1];
	int i = low, j = mid + 1, k = 0;
	while (i <= mid && j <= high) {
		if (a[i] < a[j]) {
			tmp[k++] = a[i++];
		} else {
			tmp[k++] = a[j++];
		}
	}
	while (i <= mid) {
		tmp[k++] = a[i++];
	}
	while (j <= high) {
		tmp[k++] = a[j++];
	}
	for (k = 0, i = low; i <= high; k++, i++) {
		a[i] = tmp[k];
	}
	return 0;
}

int merge_sort(int *a, int n)
{
	int start, step = 1;
	while (step < n) {
		start = 0;
		while (start + step < n) {
			if (n >= start + step * 2)
				merge(a, start, start + step - 1, start + step * 2 - 1);
			else if (n > start + step)
				merge(a, start, start + step - 1, n - 1);
			start += step * 2;
		}
		step *= 2;
	}
	return 0;
}
int main(void)
{
	int a[] = {1, 3, 5, 7, 2, 4, 6, 8, 0, -1, 15, -2, 9, 13};
	int n = sizeof(a) / sizeof(*a);
	int i;
	merge_sort(a, n);
	for (i = 0; i < n; i++)
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	return 0;
}
