#include <stdio.h>

struct data {
#define MAXSIZE	10
	int data[MAXSIZE];
	int len;
};

void data_init(struct data *data);
void data_displayer(struct data *data);
int data_insert(struct data *data, int position, int member);
int main(void)
{
	struct data data;
	int ret;
	data_init(&data);
	data_displayer(&data);
	ret = data_insert(&data, 11, 11);
	fprintf(stdout, "11, 11 result :%d\n", ret);
	ret = data_insert(&data, 9, 9);
	fprintf(stdout, "9, 9 result :%d\n", ret);
	ret = data_insert(&data, 10, 10);
	fprintf(stdout, "10, 10 result :%d\n", ret);
	ret = data_insert(&data, 10, 10);
	fprintf(stdout, "10, 10 result :%d\n", ret);
	data_displayer(&data);
	return 0;
}

void data_init(struct data *data)
{
	int i, len = 8;
	for (i = 0; i < len; i++)
		data->data[i] = i;
	data->len = len;
}
void data_displayer(struct data *data)
{
	int i;
	for (i = 0; i < data->len; i++)
		fprintf(stdout, "data[%d] :%d\n",
				i, data->data[i]);
}
enum {
	ERROR,
	OK,
};
int data_insert(struct data *data, int position, int member)
{
	int i;
	if (position > data->len + 1 || data->len >= MAXSIZE)
		return ERROR;
	
	for (i = data->len - 1; i >= position - 1; i--) {
		data->data[i + 1] = data->data[i];
	}
	data->data[position - 1] = member;
	data->len++;
	return OK;
}
