#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

int main(void)
{
#define ARRAY_SIZE	(100 * 1000 * 1000)
	long *a;
	a = malloc(sizeof(*a) * ARRAY_SIZE);
	if (!a) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	long i, tmp = 1000 * 1000 * 100, save;
	for (i = 0; i < ARRAY_SIZE; i++)
		a[i] = i;
#if 0
	for (i = 0; i < ARRAY_SIZE; i++) {
		if (a[i] == tmp) {
			fprintf(stdout, "a[%ld]:%ld\n", i, a[i]);
			break;
		}
	}
#else
	save = a[ARRAY_SIZE - 1];
	a[ARRAY_SIZE - 1] = tmp;
	i = 0;
	while (a[i] != tmp) {
		i++;
	}
	a[ARRAY_SIZE - 1] = save;
	if ((ARRAY_SIZE - 1 == i && a[ARRAY_SIZE - 1] == tmp) || i < ARRAY_SIZE - 1) {
		fprintf(stdout, "a[%ld]:%ld\n", i, a[i]);
	} else {
		fprintf(stdout, "don't fount\n");
	}
#endif
	if (a)
		free(a);
	return 0;
}
