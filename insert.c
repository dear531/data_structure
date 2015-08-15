#include <stdio.h>
#include "head.h"

int main(void)
{
	int i, j;
	int a[10] = {2, 1, 4, 3, 6, 5, 8, 7, 10, 9};
	int num = ARRAYSIZE(a);
	int tmp;
	display(a, num);
	for (i = 1; i < num; i++) {
		for (tmp = a[i], j = i - 1; j >= 0 && tmp < a[j]; j--) {
			a[j + 1] = a[j];
		}
		a[j + 1] = tmp;
	}
	display(a, num);
	return 0;
}
