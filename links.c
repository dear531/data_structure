#include <stdio.h>
#include <stdlib.h>
#include "links.h"

struct node * add_node(struct node *head, struct node
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

struct node *free_link(struct node *head)
{
	struct node *curr;
	for (curr = head; NULL != head;) {
		curr = head;
		head = head->next;
		free(curr);
	}
	return head;
}

struct node *insert_node(struct node *prev, struct node *node)
{
	if (NULL == prev || NULL == node) return NULL;
	struct node *next = prev->next;
	prev->next = node;
	node->next = next;
	return node;
}

/* myself done */
struct node *insert_sort(struct node *head, struct node* node)
{
	struct node *prev, *curr, *insert_ret = NULL, *next;
	for (curr = head; NULL != curr; prev = curr, curr = curr->next) {
		if (head == curr && node->data > curr->data) {
			next = head;
			head = node;
			node->next = next;
			break;
		} else if (node->data > curr->data) {
			insert_ret = insert_node(prev, node);
			break;
		} else if (NULL == curr->next) {
			node->next = curr->next;
			curr->next = node;
			break;
		}
	}
	return head;
}

struct node *insert_sort_from_network(struct node *head, struct node *node)
{
	if (node == NULL) return head;
	if (head == NULL) return node;
	struct node *prev, *curr;
	for (prev = curr = head; NULL != curr && curr->data > node->data; prev = curr, curr = curr->next);
	if (head == curr) {
		node->next = head;
		head = node;
	} else {
		node->next = curr;
		prev->next = node;
	}
	return head;
}

struct node *link_sort(struct node *head)
{
	struct node *new_head = NULL, *new_tail, *prev, *curr, *prev_tmp, *tmp;
	int i = 0;
	for (; NULL != head;) {
		for (prev_tmp = tmp = prev = curr = head; NULL != curr; prev = curr, curr = curr->next) {
			if (tmp->data < curr->data) {
				prev_tmp = prev;
				tmp = curr;
			}
		}
		if (head == tmp) {
			head = head->next;
		} else {
			prev_tmp->next = prev_tmp->next->next;
		}
		if (NULL == new_head) {
			new_head = new_tail = tmp;
		} else {
			new_tail->next = tmp;
			new_tail = tmp;
		}
		tmp->next = NULL;
	}
	return new_head;
}

struct node *link_sort_from_network(struct node *head)
{
	if (NULL == head) return head;
	struct node *first, *prev, *curr, *tmp;
	first = head->next;
	head->next = NULL;
	for ( ;NULL != first; ) {
		for (tmp = first, curr = head;
			(NULL != curr) && (tmp->data > curr->data);
			prev = curr, curr = curr->next) ;
		first = first->next;
		if (head == curr) {
			head = tmp;
		} else {
			prev->next = tmp;
		}
		tmp->next = curr;

	}
	return head;
}

