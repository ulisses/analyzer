#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

typedef enum {LB, EB, RB} BF;

typedef struct node {
	int n;
	BF bf;
	struct node *left;
	struct node *right;
}AVL;

AVL *insere(AVL *tree, int val)
{
	if(tree == NULL)
	{
		tree = (AVL *) malloc(sizeof(AVL));
		if(tree == NULL)
		{
			perror("ERROR: malloc");
			exit(EXIT_FAILURE);
		}
		tree->n = val;
		tree->left = tree->right = NULL;
		tree->bf = EB;
	}
	else
	{
		if(tree->n > val) // inserir a esquerda
		{
			AVL *ant, *act;
			
			for(ant = NULL, act = tree; act != NULL && tree->n > val ; ant = act, act = act->left);
		}
		if(tree->n < val) // inserir a direita
		{
			
		}
	}
	return tree;
}

void print(AVL *tree)
{
	if(tree != NULL)
	{
		print(tree->left);
		printf("%d ",tree->n);
		print(tree->right);
	}
	else puts("");
}

int main()
{
	AVL *tree=NULL;
	
	tree = insere(tree,1);
	tree = insere(tree,2);
	tree = insere(tree,3);
	//tree = ()
	print(tree);
	
	return 0;
}
