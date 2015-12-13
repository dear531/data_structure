#include <stdio.h>

int main(void)
{
	int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
	int i, j, k, tmp;
	int size = sizeof(a) / sizeof(*a);
	for (i = 1; i < size; i++) {
		tmp = a[i];
		for (j = i - 1; j >= 0 && a[j] > tmp; j--) {
				a[j + 1] = a[j];
		}
		a[j + 1] = tmp;
	}
	for (i = 0; i < size; i++) {
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	}
	return 0;
}
