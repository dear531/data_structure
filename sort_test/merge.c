#include <stdio.h>

void merge(int *array, int *tmparray, int start, int mid, int end)
{
	int i = start, j = mid + 1, k = start;
	while (i <= mid && j <= end) {
		if (array[i] > array[j])
			tmparray[k++] = array[j++];
		else
			tmparray[k++] = array[i++];
	}
	while (i <= mid) {
		tmparray[k++] = array[i++];
	}
	while (j <= end) {
		tmparray[k++] = array[j++];
	}
	for (i = start; i <= end; i++) {
		array[i] = tmparray[i];
	}
	return;
}

void merge_sort(int *array, int *tmparray, int start, int end)
{
	int mid;
	if (start >= end) 
		return;
	mid = (start + end) / 2;
	merge_sort(array, tmparray, start, mid);
	merge_sort(array, tmparray, mid + 1, end);
	merge(array, tmparray, start, mid, end);
	return;
}

int main(void)
{
	int a[9] = {1, 3, 5, 7, 2, 4, 6, 8, 1};
	int b[9];
	int size = sizeof(a) / sizeof(*a);
	int i;
	merge_sort(a, b, 0, size - 1);
	for (i = 0; i < size; i++) {
		fprintf(stdout, "a[%d] :%d\n", i, a[i]);
	}
	for (i = 0; i < size; i++) {
		fprintf(stdout, "b[%d] :%d\n", i, b[i]);
	}
	return 0;
}
