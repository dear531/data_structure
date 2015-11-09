#include <stdio.h>
#include <stdlib.h>

#define IS_STACK_NULL(stack) do {	\
	if (NULL == stack) {		\
		return -1;		\
	}				\
} while (0)
#define STACK_MAX_SIZE	50
struct link {
	int data;
	struct link *next;
};

struct stack {
	struct link *head;
	int number;
} stack;

int init_stack(struct stack *stack)
{
	IS_STACK_NULL(stack);
	stack->head = NULL;
	stack->number = 0;
	return 0;
}

int is_empty(struct stack *stack)
{
	IS_STACK_NULL(stack);
	return 0 == stack->number || NULL == stack->head;
}

int is_full(struct stack *stack)
{
	IS_STACK_NULL(stack);
	return STACK_MAX_SIZE == stack->number;
}

int clear_stack(struct stack *stack)
{
	IS_STACK_NULL(stack);
	if (NULL == stack->head) {
		goto out;
	}
	struct link *tmp = NULL;
	for (tmp = stack->head; tmp != NULL; ) {
		stack->head = stack->head->next;
		free(tmp);
		tmp = stack->head;
	}
out:
	return 0;
}

int destroy_stack(struct stack *stack)
{
	return clear_stack(stack);
}

int push_stack(struct stack *stack, int member)
{
	IS_STACK_NULL(stack);
	if (is_full(stack)) {
		fprintf(stdout, "stack is full\n");
		return 1;
	}
	struct link *tmp = NULL;
	if ((tmp = malloc(sizeof(struct link))) == NULL) {
		return -1;
	}
	tmp->data = member;
	tmp->next = stack->head;
	stack->head = tmp;
	stack->number++;
	return 0;
}

int pop_stack(struct stack *stack, int *member)
{
	IS_STACK_NULL(stack);
	if (is_empty(stack)) {
		fprintf(stdout, "stack is empty\n");
		return 1;
	}
	struct link *tmp = stack->head;
	stack->head = stack->head->next;
	stack->number--;
	*member = tmp->data;
	free(tmp);
	tmp = NULL;

	return 0;
}

int print_stack(struct stack *stack)
{
	IS_STACK_NULL(stack);
	struct link *prev, *curr;
	int i;
	for (prev = curr = stack->head, i = stack->number; NULL != curr;
			prev = curr, curr = curr->next, i--) {
		fprintf(stdout, "stack[%d]:%d\n", i, curr->data);
	}
	return 0;
}

int main(void)
{
	int i, member;
	init_stack(&stack);
	for (i = 0; i < 60; i++)
		push_stack(&stack, i);
	print_stack(&stack);
	for (i = 0; i < 60; i++) {
		pop_stack(&stack, &member);
		fprintf(stdout, "i :%d, member :%d\n",
				i, member);
	}
	push_stack(&stack, 1);
	destroy_stack(&stack);
	print_stack(&stack);
	return 0;
}
