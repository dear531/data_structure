#include <stdio.h>
#include <stdlib.h>

#include "links.h"

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

	head = link_sort(head);
	printf("link_sort\n");
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
