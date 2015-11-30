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

struct queue {
	struct tree** node;
	int front;
	int rear;
	int flag;
	int size;
};

int init_queue(struct queue *queue, int size)
{
	if (NULL == (queue->node = malloc(sizeof(queue->node) * size))) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	queue->size = size;
	queue->front = 0;
	queue->rear = 0;
	queue->flag = 0;
	return 0;
}

int destroy_queue(struct queue *queue)
{
	if (NULL != queue->node) {
		free(queue->node);
		queue->node = NULL;
	}
	queue->size = 0;
	queue->front = 0;
	queue->rear = 0;
	queue->flag = 0;
	return 0;
}

int is_queue_empty(struct queue *queue)
{
	return queue->front == queue->rear && 0 == queue->flag;
}

int is_queue_full(struct queue *queue)
{
	return queue->front == queue->rear && 1 == queue->flag;
}

void enqueue(struct queue *queue, struct tree *node)
{
	queue->node[queue->rear] = node;
	queue->rear = (queue->rear + 1) % queue->size;
	queue->flag = 1;
}

void dequeue(struct queue *queue, struct tree **node)
{
	if (NULL != node)
		*node = queue->node[queue->front];
	queue->front = (queue->front + 1) % queue->size;
	queue->flag = 0;
}

int queue_length(struct queue *queue)
{
	return (queue->size + queue->rear - queue->front);
}

void print_queue(struct queue *queue)
{
	int i, start;
	if (is_queue_full) {
		fprintf(stdout, "queue->node[%d]:%p\n",
			queue->front, queue->node[queue->front]);
		start = queue->front + 1;
	} else {
		start = queue->front;
	}
	for (i = start; i != queue->rear;
		i = (i + 1) % queue->size) {
		fprintf(stdout, "queue->node[%d]:%p\n",
			i, queue->node[i]);
	}
}

int level_tree(struct tree *tree, int size)
{
#if 0
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
#endif
#if 0
	struct tree *t[10];
	int i;
	struct queue queue1;
	init_queue(&queue1, sizeof(t) / sizeof(&t));
	fprintf(stdout, "is empty :%d\n", is_queue_empty(&queue1));
	for (i = 0; i < sizeof(t) / sizeof(*t); i++) {
		if (!is_queue_full(&queue1))
			enqueue(&queue1, t[i]);
	}
	print_queue(&queue1);
	dequeue(&queue1, NULL);
	enqueue(&queue1, (struct tree *)(1));
	print_queue(&queue1);
	fprintf(stdout, "queue length :%d\n",
			queue_length(&queue1));
	fprintf(stdout, "is full :%d\n", is_queue_full(&queue1));
#endif
#if 1
	struct queue queue1, queue2;
	int max_number = (log2(size) + 1) * 2;
	init_queue(&queue1, max_number);
	init_queue(&queue2, max_number);
	enqueue(&queue1, tree);
	struct tree *t;
	struct queue *qp1 = &queue1, *qp2 = &queue2, *qtmp;
	int count = 0;
	while (!is_queue_empty(&queue1) || !is_queue_empty(&queue2)) {
		while (!is_queue_empty(qp1)) {
			dequeue(qp1, &t);
			if (t != NULL)
				fprintf(stdout, "%d ", t->data);
			if (!is_queue_full(qp2) && NULL != t->left)
				enqueue(qp2, t->left);
			if (!is_queue_full(qp2) && NULL != t->right)
				enqueue(qp2, t->right);
		}
		fprintf(stdout, "\n");
		qtmp = qp1; qp1 = qp2; qp2 = qtmp;
	}
	destroy_queue(&queue1);
	destroy_queue(&queue2);
#endif
	return 0;

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
