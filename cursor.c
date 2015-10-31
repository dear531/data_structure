#include <stdio.h>

#define MAXSIZE	100

struct cursor {
	int data;
	int cursor;
};

#define VALID 40

int main(void)
{
	struct cursor cursor[MAXSIZE] = {{0,0}};
	int i;
	for (i = 0; i < VALID; i++) {
		cursor[i].cursor = i + 1;
	}
	int a[] = {1, 3, 5, 7, 9, 2, 4, 6, 8, 10};
	int next;
	for (next = 0, i = 0; i < sizeof(a) / sizeof(*a); i++) {
		next = cursor[next].cursor;
		cursor[next].data = a[i];
	}
	cursor[next].cursor = 0;
	cursor[0].cursor = next + 1;
	cursor[MAXSIZE - 1].cursor = 1;
	for (next = cursor[MAXSIZE - 1].cursor; next != 0; next = cursor[next].cursor) {
		printf("cursor[%d]:%d\n", next, cursor[next].data);
	}
	return 0;
}
