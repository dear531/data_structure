#include <stdio.h>

int main(void)
{
	int i, j, p, tmp;
	int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 0};
	int size = sizeof(a) / sizeof(*a);
	for (i = 0; i < size; i++) {
		fprintf(stdout, "a[%d] :%d\n", i, a[i]);
	}
	for (i = 0; i < size; i++) {
		p = i;
		for (j = 1 + i; j < size; j++) {
			if (a[j] < a[p]) {
				p = j;
			}
		}
		if (a[p] != a[i]) {
			tmp = a[p];
			a[p] = a[i];
			a[i] = tmp;
		}
	}
	for (i = 0; i < size; i++) {
		fprintf(stdout, "a[%d] :%d\n", i, a[i]);
	}
	return 0;
}
