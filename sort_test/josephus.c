#include <stdio.h>

int main(void)
{
	int a[10], i;
	int count = sizeof(a) / sizeof(*a);
	for (i = 0; i < count; i++) {
		a[i] = i;
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	}
	int tmpcount;
	i = 0;
	while (1 != count) {
		if (-1 != a[i]) {
			tmpcount++;
			if (0 == tmpcount % 5) {
				fprintf(stdout, "a[%d]:%d\n", i, a[i]);
				a[i] = -1;
				count--;
				tmpcount = 0;
			}
		}
		i = (i + 1) % (sizeof(a) / sizeof(*a));
	}
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		fprintf(stdout, "a[%d]:%d\n", i, a[i]);
	}
	return 0;
}
