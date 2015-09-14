#include <stdio.h>
#include <stdlib.h>

struct node {
	int data;
	struct node *next;
};

struct node * insert_node(struct node *head, struct node
		*member)
{
	if (NULL == member) return head;
	if (NULL == head) return member;
	member->next = head;
	head = member;
	return head;
}
void display_node(struct node *head)
{
	struct node *p = NULL;
	for (p = head; p != NULL; p = p->next) {
		printf("%d\n", p->data);
	}
}

struct node *invert_node(struct node *head)
{
	struct node *prev, *next;
	for (prev = NULL; head != NULL; ) {
			next = head->next;
			head->next = prev;
			prev = head;
			head = next;
	}
	return prev;
}
int main(void)
{
	int a[10] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 0};
	struct node *p = NULL, *head = NULL;
	int i;
	for (i = 0; i < sizeof(a) / sizeof(*a); i++) {
		p = malloc(sizeof(*p));
		p->next = NULL;
		p->data = a[i];
		head = insert_node(head, p);
	}
	display_node(head);
	head = invert_node(head);
	display_node(head);
	return 0;
}
