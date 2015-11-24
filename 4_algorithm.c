#include <stdio.h>
#include <stdlib.h>

#define IS_STACK_NULL(top) do {	\
	if (top == NULL)		\
		return -1;		\
} while(0)

struct expre {
	char c;
	char exp_num;
};

enum {
	NUMBER = 1,
	EXPRE,
	LEFT,
	RIGHT,
};

struct stack {
	struct stack *next;
	char c;
};

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

static inline int is_expre(char c)
{
	return '+' == c || '-' == c || '*' == c || '/' == c;
}

static inline int is_left(char c)
{
	return '(' == c;
}

static inline int is_right(char c)
{
	return ')' == c;
}

static int check_expre(struct expre *expre)
{
	if (NULL == expre)
		return -1;
	int i;
	char c1, c2;
	/* check head */
	if (LEFT != expre[0].exp_num && NUMBER != expre[0].exp_num) {
		fprintf(stdout, "expre[0].exp_num :%d\n", expre[0].exp_num);
		goto failure;
	}

	for (i = 0; expre[i + 1].c != 0 && expre[i + 1].exp_num != 0; i++) {
#if 1
		c1 = expre[i].exp_num;
		c2 = expre[i + 1].exp_num;
		if ((NUMBER == c1 && (EXPRE == c2 || RIGHT == c2))
		|| (EXPRE == c1 && (LEFT == c2 || NUMBER == c2)) 
		|| (LEFT == c1 && NUMBER == c2) 
		|| (RIGHT == c1 && EXPRE == c2)) {
			continue;
		} else {
			goto failure;
		}
	}
#endif
	/* check tail */
	if (RIGHT != expre[i].exp_num && NUMBER != expre[i].exp_num)
		goto failure;
	return 0;
failure:
	return 1;
}

int check_bracets(struct expre *expre)
{
	if (NULL == expre)
		return -1;
	struct stack *top = NULL;
	int i;
	init_stack(&top);
	char num;
	for (i = 0; 0 != expre[i].exp_num; i++) {
		if (LEFT == expre[i].exp_num) {
			push_stack(&top, expre[i].c);
		} else if (RIGHT == expre[i].exp_num) {
			if (is_empty(top)) {
				goto failure;
			} else {
				pop_stack(&top, &num);
			}
		}
	}
	if (0 == is_empty(top)) {
		goto failure;
	}
	return 0;
failure:
	destroy_stack(&top);
	return 1;
}

#define CHECK_EXPRE(c) ('+' != c && '-' != c  && '*' != c  && '/' != c )
int cmp_expre(char c1, char c2)
{
	if (CHECK_EXPRE(c1) || CHECK_EXPRE(c2))
		return -2;
	if (('+' == c1 || '-' == c1) && ('*' == c2 || '/' == c2))
		return -1;
	else if (('*' == c1 || '/' == c1) && ('+' == c2 || '-' == c2))
		return 1;
	else
		return 0;
}
#undef CHECK_EXPRE

int main(void)
{
#if 1
	char buff[64] = {0};
	struct expre expre[64] = {0};
	char *p;
	char *pp = NULL;
	int i;
	scanf("%s", buff);
	fprintf(stdout, "buff :%s\n", buff);
#define EXPRE_OPRAT(EXPRE_NUM) do {	\
	expre[i].c = *p;		\
	expre[i].exp_num = EXPRE_NUM;	\
	p++;				\
} while (0)
	for (i = 0, p = buff; *p != '\0'; i++) {
		if ('0' <= *p && '9' >= *p) {
			expre[i].c = strtol(p, &pp, 10);
			expre[i].exp_num = NUMBER;
			p = pp;
		} else if (is_expre(*p)) {
			EXPRE_OPRAT(EXPRE);
		} else if (is_left(*p)) {
			EXPRE_OPRAT(LEFT);
		} else if (is_right(*p)) {
			EXPRE_OPRAT(RIGHT);
		} else {
			fprintf(stderr, "invalid expression char %c\n",
					*p);
			return -1;
		}
	}
#undef EXPRE_OPRAT 
	if (0 != check_expre(expre)) {
		fprintf(stderr, "check expression is failure\n");
		return 1;
	}
	if (0 != check_bracets(expre)) {
		fprintf(stderr, "check bracets is failure\n");
		return 1;
	}
	struct expre suffix[64] = {0};
	struct stack *top = NULL;
	int j;
	char tmpc;
	init_stack(&top);
	for (i = 0, j = 0; 0 != expre[i].c && 0 != expre[i].exp_num; i++) {
		print_stack(top);
		if (NUMBER == expre[i].exp_num) {
			suffix[j++] = expre[i];
		} else if (LEFT == expre[i].exp_num) {
			push_stack(&top, expre[i].c);
		} else if (!is_empty(top) && RIGHT == expre[i].exp_num) {
				pop_stack(&top, &tmpc);
			while ('(' != tmpc) {
				suffix[j].c = tmpc;
				suffix[j].exp_num = EXPRE;
				j++;
				if (is_empty(top))
					break;
				pop_stack(&top, &tmpc);
			}
		} else if (!is_empty(top) && EXPRE == expre[i].exp_num) {
			int ret;
			pop_stack(&top, &tmpc);
			if ('(' == tmpc) {
				push_stack(&top, tmpc);
				push_stack(&top, expre[i].c);
			} else if (-2 == (ret = cmp_expre(expre[i].c, tmpc))) {
				fprintf(stderr, "%c or %c is invalid char\n",
						tmpc, expre[i].c);
				return -1;
			} else if (-1 == ret) {
				suffix[j].c = tmpc;
				suffix[j].exp_num = EXPRE;
				j++;
				while (!is_empty(top)) {
					pop_stack(&top, &tmpc);
					if ('(' == tmpc) {
						push_stack(&top, tmpc);
						break;
					}
					suffix[j].c = tmpc;
					suffix[j].exp_num = EXPRE;
					j++;
				}
				push_stack(&top, expre[i].c);
			} else {
				push_stack(&top, tmpc);
				push_stack(&top, expre[i].c);
			}
		} else if (is_empty(top) && EXPRE == expre[i].exp_num) {
				push_stack(&top, expre[i].c);
		}
	}
	while (!is_empty(top)) {
		pop_stack(&top, &tmpc);
		suffix[j].c = tmpc;
		suffix[j].exp_num = EXPRE;
		j++;
	}
	for (i = 0; 0 != suffix[i].c && 0 != suffix[i].exp_num; i++) {
		if (NUMBER == suffix[i].exp_num) {
			fprintf(stdout, "suffix[%d].c:%d\n",
					i, suffix[i].c);
		} else {
			fprintf(stdout, "suffix[%d].c:%c\n",
					i, suffix[i].c);
		}
	}
	destroy_stack(&top);
#endif
	return 0;
}
