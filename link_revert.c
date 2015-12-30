#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct node {
	struct node *next;
	int data;
};

struct node *mknode(int a)
{
	struct node *p = malloc(sizeof(*p));
	if (NULL == p) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	p->data = a;
	return p;
}

struct node *insert(struct node *head, int a)
{
	struct node *p = mknode(a);
	p->next = head;
	head = p;
	return head;
}

struct node *link_revert(struct node *head)
{
	if (NULL == head)
		return head;
	struct node *curr, *prev, *next;
	curr = head;
	next = head->next;
	while (NULL != curr) {
		curr->next = prev;
		prev = curr;
		if (NULL == next)
			break;
		curr = next;
		next = next->next;
	}
	return prev;
}

void destroy_link(struct node *head)
{
	if (NULL == head)
		return;
	struct node *curr, *next;
	for (curr = head, next = head->next;
		curr != NULL;
		curr = next, next = next != NULL ? next->next : next) {
		free(curr);
	}
	return;
}

void print_link(struct node *head)
{
	struct node *curr;
	int i;
	for (i = 0, curr = head; NULL != curr; curr = curr->next, i++)
		fprintf(stdout, "node[%d]:%d\n", i, curr->data);
}

int main(void)
{
	struct node *head = NULL;
	int a[] = {1, 3, 5, 7, 9};
	int i;
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		head = insert(head, a[i]);
	}
	print_link(head);
	head = link_revert(head);
	fprintf(stdout, "revert\n");
	print_link(head);
	destroy_link(head);
	head = NULL;
	print_link(head);
	return 0;
}

