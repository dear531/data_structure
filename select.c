#include <stdio.h>
#include "head.h"

int main(void)
{
	int a[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	int num = ARRAYSIZE(a);
	int i, j, p, tmp;
	display(a, num);
	for (i = 0; i < num; i++) {
		p = i;
		for (j = i + 1; j < num; j++) {
			if (a[p] > a[j]) {
				p = j;
			}
		}
		if (p != i) {
			tmp = a[i];
			a[i] = a[p];
			a[p] = tmp;
		}
	}
	display(a, num);
	return 0;
}
