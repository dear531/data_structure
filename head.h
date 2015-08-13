#ifndef __HEAD_H__
#define __HEAD_H__
#define ARRAYSIZE(a) (sizeof(a) / sizeof(*a))
void display(int *a, int size)
{
	int i;
	for (i = 0; i < size; i++)
		fprintf(stdout, "%d\n", a[i]);
}

#endif
