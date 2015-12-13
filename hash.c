#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

#define INIT_KEY	(-1)
#define HASH_LEN	(20)
int m = (HASH_LEN - 1);

struct hashtab {
	int *tab;
	int count;
};

int init_hashtab(struct hashtab *h, int size)
{
	int i;
	if (!h)
		return 1;
	if (NULL == (h->tab = malloc(sizeof(h->tab) * HASH_LEN))) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	for (i = 0; i < HASH_LEN; i++) {
		h->tab[i] = INIT_KEY;
	}
	h->count = 0;
	return 0;
}

int destroy_hashtab(struct hashtab *t)
{
	if (!t)
		return 1;
	if (!t->tab) {
		free(t->tab);
		t->tab = NULL;
	}
	t->count = -1;
	return 0;
}

int hash1(int key)
{
	return key % m;
}

void print_hashtab(struct hashtab *t)
{
	int i;
	for (i = 0; i < HASH_LEN; i++) {
		fprintf(stdout, "t[%d]:%d\n", i, t->tab[i]);
	}
}

int insert_hash(struct hashtab *t, int key)
{
	int add = hash1(key);
	int begin = add;
	while (t->tab[add] != INIT_KEY) {
		add = (add + 1) % m;
		fprintf(stdout, "collision\n");
		if (add == begin) {
			fprintf(stderr, "hash table is full\n");
			return 1;
		}
	}
	t->tab[add] = key;
	return 0;
}

int search_hash(struct hashtab *t, int key)
{
	int val = hash1(key);
	int begin = val;
	while (t->tab[val] != key) {
		val = (val + 1) % m;
		if (t->tab[val] == INIT_KEY || begin != val)
			return -1;
	}
	if (key == t->tab[val])
		return val;
	else
		return -1;
}

int main(void)
{
	struct hashtab tab;
	init_hashtab(&tab, HASH_LEN);
	int a[10] = {101, 222, 5, 3, 8, 10, 444, 6, 9, 10};
	int i;
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		insert_hash(&tab, a[i]);
	}
	fprintf(stdout, "search_hash :%d\n", search_hash(&tab, 10));
	print_hashtab(&tab);
	destroy_hashtab(&tab);
	return 0;
}
