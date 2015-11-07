#include <stdio.h>

#define STACK_SIZE	50
#define IS_STACK_VALID(stack) do {	\
	if (NULL == stack) {		\
		return -1;		\
	}				\
} while (0)
struct stack {
	int data[STACK_SIZE];
	int top1;
	int top2;
} stack;

int is_full(struct stack *stack)
{
	IS_STACK_VALID(stack);
	return stack->top1 == stack->top2 - 1;
}

int is_empty(struct stack *stack, int stack_num)
{
	IS_STACK_VALID(stack);
	if (1 == stack_num) {
		return -1 == stack->top1;
	} else if (2 == stack_num) {
		return sizeof(stack->data) / sizeof(*stack->data) == stack->top2;
	} else {
		fprintf(stdout, "not exists the stack number\n");
		return 1;
	}
}

int init_stack(struct stack *stack)
{
	IS_STACK_VALID(stack);
	int i;
	for (i = 0; i < sizeof(stack->data) / sizeof(*stack->data); i++) {
		stack->data[i] = 0;
	}
	stack->top1 = -1;
	stack->top2 = sizeof(stack->data) / sizeof(*stack->data);
	return 0;
}

int clear_stack(struct stack *stack, int stack_num)
{
	IS_STACK_VALID(stack);
	if (1 == stack_num) {
		for ( ; stack->top1 > -1; stack->top1--) {
			stack->data[stack->top1] = 0;
		}
	} else if (2 == stack_num) {
		for ( ; stack->top1 < sizeof(stack->data) / sizeof(*stack->data);
				stack->top2++) {
			stack->data[stack->top2] = 0;
		}
	} else {
		fprintf(stderr, "not exists stack number\n");
		return 1;
	}
	return 0;
}

int destroy_stack(struct stack *stack, int stack_num)
{
	return clear_stack(stack, stack_num);
}

int push_stack(struct stack *stack, int stack_num, int data)
{
	IS_STACK_VALID(stack);
	if (is_full(stack)) {
		fprintf(stdout, "stack is full\n");
		return 1;
	}
	if (1 == stack_num) {
		stack->data[++stack->top1] = data;
	} else if (2 == stack_num) {
		stack->data[--stack->top2] = data;
	} else {
		fprintf(stderr, "not exists stack number\n");
		return 1;
	}
	return 0;
}

int pop_stack(struct stack *stack, int stack_num, int *data)
{
	IS_STACK_VALID(stack);
	if (is_empty(stack, stack_num)) {
		fprintf(stderr, "stack is empty\n");
		return 1;
	}
	if (1 == stack_num) {
		*data = stack->data[stack->top1--];
	} else if (2 == stack_num) {
		*data = stack->data[stack->top2++];
	} else {
		fprintf(stderr, "not exists stack number\n");
		return 1;
	}
	return 0;
}

int print_stack(struct stack *stack, int stack_num)
{
	IS_STACK_VALID(stack);
	int i;
	if (1 == stack_num) {
		for (i = stack->top1; i > -1; i--) {
			fprintf(stdout, "stack->data[%d]:%d\n",
					i, stack->data[i]);
		}
	} else if (2 == stack_num) {
		for (i = stack->top2;
			i < sizeof(stack->data) / sizeof(*stack->data);
			i++) {
			fprintf(stdout, "stack->data[%d]:%d\n",
					i, stack->data[i]);
		}
	} else {
		fprintf(stderr, "not exsits stack number\n");
		return 1;
	}

	return 0;
}

int main(void)
{
	int i;
	init_stack(&stack);
	for (i = 0; i < 10; i++) {
		push_stack(&stack, 1, i);
	}
	for (i = 49; i > -1; i--) {
		push_stack(&stack, 2, i);
	}
	print_stack(&stack, 1);
	print_stack(&stack, 2);
	int data;
	pop_stack(&stack, 1, &data);
	fprintf(stdout, "stack 1 top data %d\n",
			data);
	print_stack(&stack, 1);
	pop_stack(&stack, 2, &data);
	fprintf(stdout, "stack 2 top data %d\n",
			data);
	print_stack(&stack, 2);
	destroy_stack(&stack, 1);
	destroy_stack(&stack, 2);
	return 0;
}
