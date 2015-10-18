#ifndef __LINKS_H__
#define __LINKS_H__
struct node {
	int data;
	struct node *next;
};

extern struct node * add_node(struct node *head, struct node
		*member);
extern void display_node(struct node *head);
extern struct node *invert_node(struct node *head);
extern struct node *free_link(struct node *head);
extern struct node *insert_node(struct node *prev, struct node *node);
/* myself done */
extern struct node *insert_sort(struct node *head, struct node* node);
extern struct node *insert_sort_from_network(struct node *head, struct node *node);
extern struct node *link_sort(struct node *head);
extern struct node *link_sort_from_network(struct node *head);
#endif
