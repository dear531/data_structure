#include <stdio.h>
#include <stdlib.h>

#include "links.h"

struct node *sort(struct node *head)
{
	if (head == NULL) return head;
	struct node *curr1, *prev1, *curr2, *prev2, *currtmp, *prevtmp, *tmp;
	int flag;
	for (prev1 = curr1 = head; curr1->next != NULL; prev1 = curr1, curr1 = curr1->next) {
		for (currtmp = curr1, prev2 = curr2 = curr1->next; curr2 != NULL;
				prev2 = curr2, curr2 = curr2->next) {
			if (curr2->data < currtmp->data) {
				prevtmp = prev2;
				currtmp = curr2;
			}
		}
		if (currtmp != curr1) {
			if (head != curr1 && curr1->next != currtmp) {
				prev1->next = currtmp;
				prevtmp->next = curr1;
				tmp = currtmp->next;
				currtmp->next = curr1->next;
				curr1->next = tmp;
				curr1 = currtmp;
			} else if (head == curr1 && curr1->next != currtmp) {
				head = currtmp;
				prevtmp->next = curr1;
				tmp = currtmp->next;
				currtmp->next = curr1->next;
				curr1->next = tmp;
				curr1 = head;
			} else if (head != curr1 && curr1->next == currtmp) {
				prev1->next = currtmp;
				curr1->next = currtmp->next;
				currtmp->next = curr1;
				curr1 = prev1->next;
			} else {
				head = currtmp;
				curr1->next = currtmp->next;
				currtmp->next = curr1;
				curr1 = head;
			}
		}
	}
	return head;
}

int main(void)
{
	int a[] = {2, 1, 4, 3, 6, 5, 8, 7, 10, 9, 0, 0, -3, 200};
	struct node *p = NULL, *head = NULL;
	int i;
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		p = malloc(sizeof(*p));
		p->next = NULL;
		p->data = a[i];
		head = add_node(head, p);
	}
	display_node(head);
#if 0
	head = link_sort(head);
	printf("link_sort\n");
#else
	head = sort(head);
	printf("sort\n");
#endif
	display_node(head);

	head = link_sort_from_network(head);
	printf("link_sort_from_network\n");
	display_node(head);

	printf("insert_sort -1\n");
	p = malloc(sizeof(*p));
	p->next = NULL;
	p->data = -1;
	head = insert_sort(head, p);
	display_node(head);

	printf("insert_sort_from_network -2\n");
	p = malloc(sizeof(*p));
	p->next = NULL;
	p->data = -2;
	head = insert_sort_from_network(head, p);
	display_node(head);

	printf("invert_node\n");
	head = invert_node(head);
	display_node(head);
	printf("free_link\n");
	head = free_link(head);
	printf("display_node\n");
	display_node(head);
	return 0;
}
