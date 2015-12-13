#include <stdio.h>

void quick(int *a, int l, int r)
{
	if (l >= r)
		return;
	int key = a[l];
	int left = l, right = r;
	while (l < r) {
		while (l < r && key >= a[r]) r--;
		a[l] = a[r];
		while (l < r && key <= a[l]) l++;
		a[r] = a[l];
	}
	a[l] = key;
	quick(a, left, l - 1);
	quick(a, l + 1, right);
	return;
}

int main(void)
{
	int a[] = {-1, 0, 0, 1, 2, 4, 3};
	int i;
	quick(a, 0, sizeof(a) / sizeof(*a) - 1);
	for (i = 0; i < sizeof(a) / sizeof(*a); i++)
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	return 0;
}
