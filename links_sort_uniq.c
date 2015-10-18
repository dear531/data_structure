#include <stdio.h>
#include <stdlib.h>

#include "links.h"

struct node *cmp_add_links(struct node *head, int data)
{
	struct node *p, *curr, *prev;
	if (head == NULL) {
		p = malloc(sizeof(*head));
		p->data = data;
		head = p;
		return head;
	}
	for (prev = curr = head; NULL != curr; prev = curr, curr = curr->next) {
		if (curr->data < data) {
			break;
		} else if (curr->data == data) {
			return head;
		}
	}
	
	p = malloc(sizeof(*head));
	p->data = data;
	if (curr == head) {
		head = p;
	} else {
		prev->next = p;
	}
	p->next = curr;
	return head;
}

int main(void)
{
	int a[] = {1, 2, 1, 0, 3, 100, 0, -1};
	int num = ARRAYSIZE(a);
	int i;
	struct node *head = NULL;
	for (i = 0; i < num; i++) {
		head = cmp_add_links(head, a[i]);
#define DEBUG	0
#if DEBUG
		printf("a[%d]:%d\n", i, a[i]);
#endif
	}
	display_node(head);
	return 0;
}
