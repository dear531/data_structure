#include <stdio.h>

#define STACKSIZE	50

struct stack {
	int a[STACKSIZE];
	int top_element;
} stack;

int init_stack(struct stack *stack)
{
	if (NULL == stack)
		return -1;
	stack->top_element = -1;
	return 0;
}

int clear_stack(struct stack *stack)
{
	if (NULL == stack)
		return -1;
	while (stack->top_element > -1) {
		stack->a[stack->top_element--] = -1;
	}
	return 0;
}

int is_full(struct stack *stack)
{
	return stack->top_element == sizeof(stack->a) / sizeof(*(stack->a)) - 1;
}

int is_empty(struct stack *stack)
{
	return stack->top_element == -1;
}

void print_stack(struct stack *stack)
{
	int i;
	for (i = stack->top_element; i > -1; i--) {
		printf("stack->a[%d] :%d\n", i, stack->a[i]);
	}
}

int push_stack(struct stack *stack, int member)
{
	if (NULL == stack) {
		return -1;
	}
	if (1 == is_full(stack)) {
		fprintf(stderr, "stack is full\n");
		return -1;
	}
	stack->a[++(stack->top_element)] = member;
	return 0;
}

int pop_stack(struct stack *stack, int *member)
{
	if (NULL == stack || NULL == member)
		return -1;
	if (1 == is_empty(stack)) {
		fprintf(stderr, "stack is empty\n");
		return -1;
	}
	*member = stack->a[(stack->top_element)--];
	return 0;
}

int destroy_stack(struct stack *stack)
{
	
	return clear_stack(stack);
}

int main(void)
{
	int i;
	init_stack(&stack);
	for (i = 0; i < STACKSIZE + 1; i++) {
		push_stack(&stack, i);
	}
	print_stack(&stack);
	int member;
	pop_stack(&stack, &member);
	fprintf(stdout, "member :%d\n", member);
	print_stack(&stack);
	clear_stack(&stack);
	fprintf(stdout, "here is second print\n");
	print_stack(&stack);
	pop_stack(&stack, &member);
	destroy_stack(&stack);
	return 0;
}
