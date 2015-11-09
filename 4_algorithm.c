#include <stdio.h>
#include <stdlib.h>

#define IS_STACK_NULL(top) do {	\
	if (top == NULL)		\
		return -1;		\
} while(0)

struct stack {
	struct stack *next;
	char c;
} *top = NULL;

int is_empty(struct stack *top)
{
	IS_STACK_NULL(top);
	return NULL == top;
}

int init_stack(struct stack **top_p)
{
	IS_STACK_NULL(top_p);
	*top_p = NULL;
	return 0;
}

int clear_stack(struct stack **top_p)
{
	IS_STACK_NULL(top_p);
	if (is_empty(*top_p)) {
		goto out;
	}
	struct stack *tmp;
	for (tmp = *top_p; NULL != tmp; ) {
		*top_p = (*top_p)->next;
		free(tmp);
		tmp = *top_p;
	}
out:
	return 0;
}

int destroy_stack(struct stack **top_p)
{
	return clear_stack(top_p);
}

int push_stack(struct stack **top_p, char c)
{
	IS_STACK_NULL(top_p);
	struct stack *tmp = NULL;
	if (NULL == (tmp = malloc(sizeof(*tmp)))) {
		return 1;
	}
	/* FIXME */
	tmp->c= c;
	tmp->next = *top_p;
	*top_p = tmp;
	return 0;
}

int pop_stack(struct stack **top_p, char *c_p)
{
	IS_STACK_NULL(top_p);
	if (is_empty(*top_p)) {
		fprintf(stderr, "stack is empty\n");
		return 1;
	}
	struct stack *tmp = NULL;
	tmp = *top_p;
	*top_p = (*top_p)->next;
	*c_p = tmp->c;
	free(tmp);
	tmp = NULL;
	return 0;
}

int print_stack(struct stack *top)
{
	IS_STACK_NULL(top);
	struct stack *prev, *curr;
	int i;
	for (i = 0, prev = curr = top; NULL != curr;
		prev = curr, curr = curr->next, i++) {
		fprintf(stdout, "c[%d]:%c\n",
				i, curr->c);
	}
	return 0;
}

int is_valid(char c)
{
	char valid[] = "+-*/()[]{}";
	int i;
	for (i = 0; i < sizeof(valid) / sizeof(*valid) - 1; i++) {
		if (c == valid[i]) {
			return 0;
		}
	}
	return 1;
}
int main(void)
{
#if 1
	/* test code */
	char c = '0';
	int i;
	init_stack(&top);
	for (i = 0; i < 10; i++) {
		push_stack(&top, c+i);
	}
	print_stack(top);
	for (i = 0; i < 11; i++) {
		if (0 == pop_stack(&top, &c))
			fprintf(stdout, "c[%d]:%c\n", i, c);
	}
	destroy_stack(&top);
#endif
	return 0;
}
