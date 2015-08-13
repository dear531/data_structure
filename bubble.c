#include <stdio.h>
#define ARRAYSIZE(a) (sizeof(a) / sizeof(*a))
void display(int *a, int size)
{
	int i;
	for (i = 0; i < size; i++)
		fprintf(stdout, "%d\n", a[i]);
}

int main(void)
{
	int i, j, a[10] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10}, tmp;
	int num = ARRAYSIZE(a);
	int swap, count = 0;
	display(a, num);
	for (i = 0; i < num - 1; i++) {
		printf("count :%d\n", ++count);
		swap = 0;
		for (j = 0; j < num - 1 - i; j++) {
			if (a[j] > a[j + 1]) {
				tmp = a[j];
				a[j] = a[j + 1];
				a[j + 1] = tmp;
				swap = 1;
			}
		}
		if (0 == swap) {
			printf("i is %d break\n", i);
			break;
		}
		display(a, num);
	}
	display(a, num);
	return 0;
}
