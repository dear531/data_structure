#include <stdio.h>

int main(void)
{
	int a[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	int size = sizeof(a) / sizeof(*a);
	int i, j, tmp, count, flag;
	for (i = 0; i < size; i++) {
		fprintf(stdout, "a[%d] :%d\n", i, a[i]);
	}
	count = 0;
	for (i = 0; i < size -1 && 0 == flag; i++) {
		for (flag = 0, j = 0; j < size - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				flag = 1;
			}
			count++;
		}
	}
	fprintf(stdout, "count :%d\n", count);
	for (i = 0; i < size; i++) {
		fprintf(stdout, "a[%d] :%d\n", i, a[i]);
	}
	return 0;
}
