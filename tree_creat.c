#include <stdio.h>
#include <stdlib.h>

struct tree {
	char ch;
	struct tree *left;
	struct tree *right;
};


int tree_create(struct tree **tree)
{
	char ch;
	scanf("%c", &ch);
	if ('#' == ch) {
		tree = NULL;
	} else {
		*tree = malloc(sizeof(**tree));
		(*tree)->ch = ch;
		tree_create(&((*tree)->left));
		tree_create(&((*tree)->right));
	}
	return 0;
}

void print_tree(struct tree *tree)
{
	if (NULL == tree)
		return;
	fprintf(stdout, "%c\n", tree->ch);
	print_tree(tree->left);
	print_tree(tree->right);
}

void destroy_tree(struct tree *tree)
{
	if (NULL == tree)
		return;
	destroy_tree(tree->left);
	destroy_tree(tree->right);
	free(tree);
}

int main(void)
{
	struct tree *tree;
	tree_create(&tree);
	print_tree(tree);
	destroy_tree(tree);
	return 0;
}
