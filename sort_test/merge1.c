#include <stdio.h>

void merge(int *array, int start, int mid, int end)
{
	int i = start, j = mid + 1, k = 0;
	int tmparray[end - start + 1];
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
	for (i = start, k = 0; i <= end; i++, k++) {
		array[i] = tmparray[k];
	}
	return;
}

void merge_sort(int *array, int start, int end)
{
	int mid;
	if (start >= end) 
		return;
	mid = (start + end) / 2;
	merge_sort(array, start, mid);
	merge_sort(array, mid + 1, end);
	merge(array, start, mid, end);
	return;
}

int main(void)
{
	int a[9] = {1, 3, 5, 7, 2, 4, 6, 8, 1};
	int size = sizeof(a) / sizeof(*a);
	int i;
	merge_sort(a, 0, size - 1);
	for (i = 0; i < size; i++) {
		fprintf(stdout, "a[%d] :%d\n", i, a[i]);
	}
	return 0;
}
