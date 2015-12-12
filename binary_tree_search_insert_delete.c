#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>

struct tree {
	int data;
	struct tree *l;
	struct tree *r;
};

struct tree *search_tree(struct tree *t, int data)
{
	if (NULL == t) {
		return NULL;
	} else if (data == t->data) {
		return t;
	} else if (data > t->data) {
		return search_tree(t->r, data);
	} else {
		return search_tree(t->l, data);
	}
}

static void *make_node(int size)
{
	void *p = NULL;
	if (NULL == (p = malloc(size))) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	return p;
}

static int insert_tree(struct tree **t, int data)
{
	if (NULL == *t) {
		*t = make_node(sizeof(**t));
		(*t)->l = (*t)->r = NULL;
		(*t)->data = data;
#if 1
	} else if (NULL != search_tree(*t, data)) {
		return 1;
#endif
	} else if (data > (*t)->data) {
		/* greater than */
		insert_tree(&((*t)->r), data);
	} else {
		/* less than */
		insert_tree(&((*t)->l), data);
	}
	return 0;
}

void init_tree(struct tree **t, int *a, int n)
{
	int i;
	for (i = 0; i < n; i++) {
		insert_tree(t, a[i]);
	};
}

static void preorder(struct tree *t)
{
	if (NULL == t)
		return;
	preorder(t->l);
	fprintf(stdout, "%d\n", t->data);
	preorder(t->r);
}

static void destroy_tree(struct tree *t)
{
	if (NULL == t)
		return;
	destroy_tree(t->l);
	destroy_tree(t->r);
	free(t);
}

void delete_node(struct tree **t)
{
	struct tree *q, *s;
	if (NULL == (*t)->l) {
		q = *t;
		(*t) = (*t)->r;
		free(q);
	} else if (NULL == (*t)->r) {
		q = *t;
		(*t) = (*t)->l;
		free(q);
	} else {
		q = *t;
		s = (*t)->l;
		while (s->r) {
			q = s;
			s = s->r;
		}
		(*t)->data = s->data;
		if (q != *t)
			q->r = s->l;
		else
			q->l = s->l;
		free(s);
	}
	return;
}

static int delete_tree(struct tree **t, int data)
{
	if (NULL == (*t)) {
		return 1;
	} else if (data == (*t)->data) {
		delete_node(t);
		return 0;
	} else if (data > (*t)->data) {
		delete_tree(&(*t)->r, data);
	} else {
		delete_tree(&(*t)->l, data);
	}
}

int main(void)
{
	struct tree *t = NULL;
	int a[] = {1, 2, 3, 4, 5, 6};
	init_tree(&t, a, sizeof(a) / sizeof(*a));
	preorder(t);
	struct tree *r = search_tree(t, 5);
	if (NULL != r)
		fprintf(stdout, "r->data:%d\n", r->data);
	delete_tree(&t, 5);
	preorder(t);
	destroy_tree(t);
	return 0;
}
