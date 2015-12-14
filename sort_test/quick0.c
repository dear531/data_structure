#include <stdio.h>

void quick(int *a, int left, int right)
{
	if (left >= right)
		return;
	int l = left, r = right;
	int key = a[r];
	while (l < r) {
		while (l < r && key >= a[l]) l++;
		a[r] = a[l];
		while (l < r && key <= a[r]) r--;
		a[l] = a[r];
	}
	a[r] = key;
	quick(a, left, r - 1);
	quick(a, r + 1, right);
	return;
}

int main(void)
{
	int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
	int i;
	quick(a, 0, sizeof(a) / sizeof(*a) - 1);
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	}
	return 0;
}
