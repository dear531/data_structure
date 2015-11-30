#include <stdio.h>
#include <string.h>
#include <errno.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <errno.h>

struct tree {
	struct tree *left;
	struct tree *right;
	int data;
};

void order(struct tree *tree, int mod)
{
	if (NULL == tree)
		return;
	if (0 == mod)
		fprintf(stdout, "%d\n", tree->data);
	order(tree->left, 0);
	if (1 == mod)
		fprintf(stdout, "%d\n", tree->data);
	order(tree->right, 0);
	if (2 == mod)
		fprintf(stdout, "%d\n", tree->data);
}

struct tree *make_node(int data)
{
	struct tree *p = malloc(sizeof(*p));
	if (NULL == p) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	p->data = data;
	return p;
}

struct tree *init_tree(int *a, int curr, int total)
{
	struct tree *p = make_node(a[curr]);
	p->left = (curr + 1) * 2 - 1 > total ? NULL
		: init_tree(a, (curr + 1) * 2 - 1, total);
	p->right = (curr + 1) * 2 > total ? NULL
		: init_tree(a, (curr + 1) * 2, total);
	return p;
}

void destroy_tree(struct tree *tree)
{
	if (NULL != tree->left)
		destroy_tree(tree->left);
	if (NULL != tree->right)
		destroy_tree(tree->right);
	free(tree);
	return;
}

int depth(struct tree *tree)
{
	if (NULL == tree)
		return 0;
	int dl = depth(tree->left);
	int dr = depth(tree->right);
	return 1 + (dl > dr ? dl : dr);
}

static int count(struct tree *tree)
{
	if (NULL == tree)
		return 0;
	else
		return 1 + count(tree->left) +
			count(tree->right);
}

struct stack {
	int top1;
	int top2;
	struct tree** node;
	int size;
};

int init_stack(struct stack *stack, int data_size)
{
	if (NULL == (stack->node= 
		malloc(sizeof(*stack->node) * (data_size + 1)))) {
		fprintf(stderr, "init_stack error :%s\n",
				strerror(errno));
		return -1;
	}
	stack->top1 = -1;
	stack->top2 = data_size;
	stack->size = data_size;
	return 0;
}

int destroy_stack(struct stack *stack)
{
	if (NULL != stack->node) {
		free(stack->node);
		stack->node = NULL;
	}
	stack->size = 0;
	return 0;
}

static int is_stack1_empty(struct stack *stack)
{
	return stack->top1 == -1;
}

static int is_stack2_empty(struct stack *stack)
{
	return stack->top2 == stack->size;
}

static void stack1_push(struct stack *stack, struct tree *node)
{
	stack->top1++;
	stack->node[stack->top1] = node;
}

static void stack2_push(struct stack *stack, struct tree *node)
{
	stack->top2--;
	stack->node[stack->top2] = node;
}

static struct tree *stack1_pop(struct stack *stack)
{
	return stack->node[stack->top1--];
}

static struct tree *stack2_pop(struct stack *stack)
{
	return stack->node[stack->top2++];
}

static int is_stack_full(struct stack *stack)
{
	return stack->top1 + 1 == stack->top2;
}

int level_tree(struct tree *tree, int size)
{
	int max_number = (log2(size) + 1) * 2;
	struct stack stack;
	init_stack(&stack, max_number);
	stack1_push(&stack, tree);
	void (*push)(struct stack*, struct tree*) = stack2_push;
	static int (*stack_empty)(struct stack *stack) = is_stack1_empty;
	struct tree *(*pop)(struct stack *) = stack1_pop;
	struct tree *t;
	while (!is_stack1_empty(&stack) ||
		!is_stack2_empty(&stack)) {
		while (!stack_empty(&stack)) {
			t = pop(&stack);
			if (NULL != t)
				fprintf(stdout, "%d ", t->data);
			if (NULL != t && !is_stack_full(&stack))
				push(&stack, t->left);
			if (NULL != t && !is_stack_full(&stack))
				push(&stack, t->right);
		}
		fprintf(stdout, "\n");
		push = (push == stack1_push ? stack2_push : stack1_push);
		pop = (pop == stack1_pop ? stack2_pop : stack1_pop);
		stack_empty = (stack_empty == is_stack1_empty ? is_stack2_empty : is_stack1_empty);
	}
	destroy_stack(&stack);
	return ;
}

int main(void)
{
	struct tree *root;
	int a[] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
	root = init_tree(a, 0, sizeof(a) / sizeof(*a) - 1);
	order(root, 0);
	fprintf(stdout, "====\n");
	order(root, 1);
	fprintf(stdout, "====\n");
	order(root, 0);
	fprintf(stdout, "depth :%d\n", depth(root));
	fprintf(stdout, "count :%d\n", count(root));
	fprintf(stdout, "sizeof (a):%ld\n", sizeof(a) /
			sizeof(*a));
	level_tree(root, sizeof(a) / sizeof(*a));
	//destroy_tree(root);
	root = NULL;
	return 0;
}
