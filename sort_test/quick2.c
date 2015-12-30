#include <stdio.h>

void quick(int *a, int low, int high)
{
	if (low >= high)
		return;
	int l = low, h = high;
	int key = a[l];
	while (l < h) {
		while (l < h && a[h] >= key)
			h--;
		a[l] = a[h];
		while (l < h && a[l] <= key)
			l++;
		a[h] = a[l];
	}
	a[l] = key;
	quick(a, low, l - 1);
	quick(a, l + 1, high);
	return;
}

int main(void)
{
	int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
	int i;
	quick(a, 0, sizeof(a) / sizeof(*a) - 1);
	for (i = 0; i < sizeof(a) / sizeof(*a); i++)
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	return 0;
}
