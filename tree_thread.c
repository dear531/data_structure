#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct tree {
	struct tree *l;
	struct tree *r;
	int ltag;
	int rtag;
	char data;
};

struct tree *init_tree(void)
{
	struct tree *t;
	char ch;
	scanf("%c", &ch);
	if ('#' == ch) {
		return NULL;
	}
	if (NULL == (t = malloc(sizeof(*t)))) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	t->data = ch;
	t->l = init_tree();
	t->r = init_tree();
	return t;
}

static void preorder(struct tree *t)
{
	if (t == NULL)
		return;
	preorder(t->l);
	fprintf(stdout, "%c\n", t->data);
	preorder(t->r);

}
#if 0
struct node {
	struct tree *t;
	struct node *next;
};
#endif

struct stack {
	struct node {
		struct tree *t;
		struct node *next;
	} *top;
	//struct node *top;
	int count;
};

static void init_stack(struct stack *s)
{
	s->top = NULL;
	s->count = 0;
}

static void *make_node(long size)
{
	void *node; 
	if (NULL == (node = malloc(size))) {
		fprintf(stderr, "malloc error %s\n", strerror(errno));
		exit(EXIT_FAILURE);
	}
	return node;
}

static void push_stack(struct stack *s, struct tree *t) 
{
	struct node *node = make_node(sizeof(*node));
	node->t = t;
	node->next = s->top;
	s->top = node;
	s->count++;
}

static struct tree * pop_stack(struct stack *s)
{
	struct node *node;
	struct tree *t;
	node = s->top;
	s->top = s->top->next;
	s->count--;
	t = node->t;
	free(node);
	return t;
}

static inline int is_stack_empty(struct stack *s)
{
	return 0 == s->count || NULL == s->top;
}

static inline int stack_number(struct stack *s)
{
	return s->count;
}

static void destroy_stack(struct stack *s)
{
	while (!is_stack_empty(s)) {
		pop_stack(s);
	}
}

static void print_stack(struct stack *s)
{
	int i;
	struct node *node;
	for (i = s->count, node = s->top; 0 < i && NULL != node; i--, node = node->next) {
		fprintf(stdout, "stack[%d]:%p\n", i, node->t);
	}
}

static void pre_in_order_nonrecursive(struct tree *t)
{
	struct tree *tmpt = t;
	struct stack s1, s2;
	init_stack(&s1);
	while (tmpt || !is_stack_empty(&s1)) {
		while (tmpt) {
			fprintf(stdout, "%c\n", tmpt->data);
			push_stack(&s1, tmpt);
			tmpt = tmpt->l;
		}
		if (!is_stack_empty(&s1)) {
			tmpt = pop_stack(&s1);
			tmpt = tmpt->r;
		}
	}
	destroy_stack(&s1);
}

static void postorder_nonrecursive(struct tree *t)
{
	struct tree *tmpt;
	struct stack s1, s2;
	init_stack(&s1);
	init_stack(&s2);
	if (t)
		push_stack(&s1, t);
	while (!is_stack_empty(&s1)) {
		tmpt = pop_stack(&s1);
		push_stack(&s2, tmpt);
		if (tmpt->l)
			push_stack(&s1, tmpt->l);
		if (tmpt->r)
			push_stack(&s1, tmpt->r);
	}
	while (!is_stack_empty(&s2)) {
		fprintf(stdout, "%c\n", pop_stack(&s2)->data);
	}
	destroy_stack(&s1);
	destroy_stack(&s2);
}

int main(void)
{
#if 0
	struct tree *t[10];
	struct stack s1;
	int i;
	init_stack(&s1);
	for (i = 0; sizeof(t) / sizeof(*t) > i; i++) {
		push_stack(&s1, t[i]);
		fprintf(stdout, "t[%d]:%p\n", i, t[i]);
	}
	print_stack(&s1);
	fprintf(stdout, "stack length :%d\n", stack_number(&s1));	
	fprintf(stdout, "pop_stack top :%p\n", pop_stack(&s1));
	fprintf(stdout, "stack length :%d\n", stack_number(&s1));	
	destroy_stack(&s1);
	print_stack(&s1);
#endif
#if 1
	struct tree *tree;
	tree = init_tree();
	preorder(tree);
	fprintf(stdout, "pre_in_order_nonrecursive\n");
	pre_in_order_nonrecursive(tree);
	fprintf(stdout, "postorder_nonrecursive\n");
	postorder_nonrecursive(tree);
#endif
	return 0;
}
