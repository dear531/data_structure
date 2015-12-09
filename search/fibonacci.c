#include <stdio.h>

int main(void)
{
	int i, n = 10, f0 = 0, f1 = 1, f;
	for (i = n; i > 0; i--) {
		if (0 == n)
			f = f0;
		else if (1 == n) {
			f = f0 + f1;
		} else {
			f0 = f1;
			f1 = f;
			f = f0 + f1;
		}
		fprintf(stdout, "%d ", f);
	}
	fprintf(stdout, "\n");
	fprintf(stdout, "f%d:%d\n", n, f);
	return 0;
}
