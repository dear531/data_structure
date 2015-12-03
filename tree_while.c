#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

struct node {
	struct tree *t;
	struct node *next;
};

struct queue {
	struct node *front;
	struct node *rear;
	int count;
};

static int init_queue(struct queue *queue)
{
	queue->rear = queue->front = NULL;
	queue->count = 0;
	return 0;
}

static inline int is_queue_empty(struct queue *queue)
{
	return (NULL == queue->rear && NULL == queue->front)
		|| 0 == queue->count;
}

static int enqueue(struct queue *queue, struct tree *t)
{
	struct node *node;
	if (NULL == (node = malloc(sizeof(*node)))) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	node->next = NULL;
	node->t = t;
	if (NULL == queue->rear && NULL == queue->front) {
		queue->rear = queue->front = node;
	} else {
		queue->rear->next = node;
		queue->rear = node;
	}
	queue->count++;
	return 0;
}

struct tree *dequeue(struct queue *queue)
{
	struct tree *t;
	struct node *node;
	node = queue->front;
	t = node->t;
	queue->front = queue->front->next;
	free(node);
	node = NULL;
	queue->count--;
	if (NULL == queue->front || 0 == queue->count)
		queue->rear = NULL;
	return t;
}

void destroy_queue(struct queue *queue)
{
	while (!is_queue_empty(queue)) {
		dequeue(queue);
	}
}

int queue_length(struct queue *queue)
{
	return queue->count;
}

void print_queue(struct queue *queue)
{
	struct node *node;
	int i;
	for (i = 0, node = queue->front; NULL != node;
			node = node->next, i++) {
		fprintf(stdout, "node[%d]->t:%p\n", i, node->t);
	}
}

struct tree {
	char c;
	struct tree *l;
	struct tree *r;
};

struct tree *init_tree(void)
{
	char ch;
	scanf("%c", &ch);
	if ('#' == ch) {
		return NULL;
	}
	struct tree *t;
	if (NULL == (t = malloc(sizeof(*t)))) {
		fprintf(stderr, "malloc error %s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	t->c = ch;
	t->l = init_tree();
	t->r = init_tree();
	return t;
}

static void destroy_tree(struct tree *t)
{
	if (NULL == t)
		return;
	destroy_tree(t->l);
	destroy_tree(t->r);
	free(t);
}

static void inorder_tree_recurs(struct tree *tree)
{
	if (NULL == tree)
		return;
	fprintf(stdout, "%c\n", tree->c);
	inorder_tree_recurs(tree->l);
	inorder_tree_recurs(tree->r);
}

struct stack {
	struct node *top;
	int count;
};

static void init_stack(struct stack *s)
{
	s->top = NULL;
	s->count = 0;
}

static int push_stack(struct stack *s, struct tree *t)
{
	struct node *node;
	if (NULL == (node = malloc(sizeof(*node)))) {
		fprintf(stderr, "malloc error :%s\n",
				strerror(errno));
		exit(EXIT_FAILURE);
	}
	node->t = t;
	node->next = s->top;
	s->top = node;
	s->count++;
	return 0;
}

static struct tree *pop_stack(struct stack *s)
{
	struct node *node;
	struct tree *t;
	node = s->top;
	s->top = s->top->next;
	t = node->t;
	free(node);
	node = NULL;
	s->count--;
	return t;
}

static int is_stack_empty(struct stack *s)
{
	return 0 == s->count || NULL == s->top;
}

static void destroy_stack(struct stack *s)
{
	while (!is_stack_empty(s)) {
		pop_stack(s);
	}
}

static int stack_number(struct stack *s)
{
	return s->count;
}

static void print_stack(struct stack *s)
{
	int i;
	struct node *node;
	for (i = s->count, node = s->top;
		0 < i && node != NULL; i--, node = node->next) {
		fprintf(stdout, "stack[%d]:%p\n", i, node->t);
	}
}

int main(void)
{
#if 0
	struct tree *tree;
	tree = init_tree();
	inorder_tree_recurs(tree);
#endif
#if 0
	struct tree *t[10], *tmpt;
	int i;
	struct queue q;
	init_queue(&q);
	for (i = 0; sizeof(t) / sizeof(*t) > i; i++) {
		enqueue(&q, t[i]);
		fprintf(stdout, "t[%d]:%p\n", i, t[i]);
	}
	print_queue(&q);
	fprintf(stdout, "queue_lenght %d\n", queue_length(&q));
	i = 0;
	while (!is_queue_empty(&q)) {
		tmpt = dequeue(&q);
		fprintf(stdout, "tmpt %d :%p\n", i++, tmpt);
	}
	print_queue(&q);
	fprintf(stdout, "queue_lenght %d\n", queue_length(&q));
	destroy_queue(&q);
#endif
#if 1
	struct tree *tree;
	tree = init_tree();
	fprintf(stdout, "inorder_tree_recurs\n");
	inorder_tree_recurs(tree);

	fprintf(stdout, "level order loop\n");
	struct queue q;
	init_queue(&q);
	enqueue(&q, tree);

	int enqueue_inc, dequeue_dec;
	dequeue_dec = queue_length(&q);
	enqueue_inc = 0;
	struct tree *tmpt;
	while (!is_queue_empty(&q)) {

		tmpt = dequeue(&q);
		dequeue_dec--;
		if (NULL == tmpt)
			fprintf(stdout, "#");
		else
			fprintf(stdout, "%c ", tmpt->c);
		if (NULL != tmpt) {
			enqueue(&q, tmpt->l);
			enqueue_inc++;
		}
		if (NULL != tmpt) {
			enqueue(&q, tmpt->r);
			enqueue_inc++;
		}

		if (0 == dequeue_dec) {
			dequeue_dec = enqueue_inc;
			enqueue_inc = 0;
			fprintf(stdout, "\n");
		}
	}
	destroy_queue(&q);
	
	fprintf(stdout, "inorder for loop\n");
	struct stack s;
	init_stack(&s);
	tmpt = tree;
	while (NULL != tmpt || !is_stack_empty(&s)) {
		fprintf(stdout, "%c\n", tmpt->c);
		if ((NULL != tmpt->l) && (NULL != tmpt->r)) {
			/* l to assinment tmpt and r push_stack */
			push_stack(&s, tmpt->r);
			tmpt = tmpt->l;
		} else if (NULL == tmpt->l && NULL != tmpt->r) {
			/* r to assinment tmpt */
			tmpt = tmpt->r;
		} else if (NULL != tmpt->l && NULL == tmpt->r) {
			/* l to assinment tmpt */
			tmpt = tmpt->l;
		} else if (NULL == tmpt->l && NULL == tmpt->r && !is_stack_empty(&s)) {
			/* dequeue to tmpt */
			tmpt = pop_stack(&s);
		} else {
			break;
		}
	}
	destroy_stack(&s);
	destroy_tree(tree);
	tree = NULL;
#endif
#if 0
	struct tree *t[10], *tmpt;
	struct stack s;
	int i;
	init_stack(&s);
	for (i = 0; 10 > i; i++) {
		push_stack(&s, t[i]);
	}
	print_stack(&s);
	for (i = 0; 5 > i; i++) {
		tmpt = pop_stack(&s);
		fprintf(stdout, "tmpt [%d]:%p\n", i, tmpt);
	}
	print_stack(&s);
	while (!is_stack_empty(&s)) {
		pop_stack(&s);
	}
	print_stack(&s);
	destroy_stack(&s);
#endif
	return 0;
}
