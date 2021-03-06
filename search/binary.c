#include <stdio.h>

int main(void)
{
	int a[1000];
	int i, tmp, search = 8;
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		a[i] = 2 * i;
	}
	int begin = 0, mid, end = sizeof(a) / sizeof(*a) - 1;
	while (begin <= end) {
		/* optimized mid value search for balance destribution */
		mid = (end - begin) * (search - a[begin]) / (a[end] - a[begin]);
		if (search > a[mid]) {
			begin = mid + 1;
		} else if (search < a[mid]) {
			end = mid - 1;
		} else {
			fprintf(stdout, "fount :a[%d]:%d\n",
					mid, a[mid]);
			break;
		}
		fprintf(stdout, "in loop begin mid end :%d %d %d\n",
				begin, mid, end);
	}
	if (a[mid] != search) {
		fprintf(stdout, "don't fount\n");
	}
	return 0;
}
