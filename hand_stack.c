#include <stdio.h>
#include <stdlib.h>

#define STACK_SIZE	20
struct stack {
	int *a;
	int top_element;
} stack = {
	.a = NULL,
	.top_element = -1
};

int init_stack(struct stack *stack, int num)
{
	if (NULL == stack || 0 > num) {
		return -1;
	}
	stack->a = malloc(sizeof(stack->a) * num);
	if (NULL == stack->a) {
		return -1;
	}
	stack->top_element = -1;
	return 0;
}

int destroy_stack(struct stack *stack)
{
	if (NULL == stack || NULL == stack->a) {
		return -1;
	}
	free(stack->a);
	stack->a = NULL;
	stack->top_element = -1;
	return 0;
}

int clean_stack(struct stack *stack)
{
	if (NULL == stack || NULL == stack->a) {
		return -1;
	}
	for ( ; -1 < stack->top_element; stack->top_element--) {
		stack->a[stack->top_element] = -1;
	}
	return 0;
}

int is_full(struct stack *stack)
{
	if (NULL == stack || NULL == stack->a) {
		return -1;
	}
	return stack->top_element == STACK_SIZE - 1;
}

int is_empty(struct stack *stack)
{
	if (NULL == stack || NULL == stack->a) {
		return -1;
	}
	return stack->top_element == -1;
}

int push_stack(struct stack *stack, int member)
{
	if (NULL == stack || NULL == stack->a) {
		return -1;
	}
	if (is_full(stack)) {
		fprintf(stderr, "stack is full\n");
		return 1;
	}
	stack->a[++stack->top_element] = member;
	return 0;
}

#if 1
int pop_stack(struct stack *stack, int *member)
{
	if (NULL == stack || NULL == stack->a) {
		return -1;
	}
	if (is_empty(stack)) {
		fprintf(stdout, "stack is empty\n");
		return 1;
	}
	*member = stack->a[stack->top_element--];
	return 0;
}
#endif

void print_stack(struct stack *stack)
{
	if (NULL == stack || NULL == stack->a) {
		return;
	}
	int i;
	for (i = stack->top_element; -1 < i; i--) {
		fprintf(stdout, "stack->a[%d]:%d\n", i, stack->a[i]);
	}
	return;
}

int main(void)
{
	init_stack(&stack, STACK_SIZE);
	int i, member;
	for (i = 0; STACK_SIZE > i; i++) {
		push_stack(&stack, i);
	}
	print_stack(&stack);
	push_stack(&stack, 0);
	clean_stack(&stack);
	pop_stack(&stack, &member);
	destroy_stack(&stack);
	return 0;
}
