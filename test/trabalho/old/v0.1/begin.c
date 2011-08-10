#include <stdio.h>
#include <stdlib.h>

typedef char TreeEntry;
typedef enum balancefactor {LH , EH , RH} BalanceFactor;
typedef struct treenode TreeNode;

struct treenode {
    BalanceFactor bf;
    TreeEntry entry;
    TreeNode *left;
    TreeNode *right;
};

typedef struct node {
    int i;
    struct node *prox;
}Node;

Node* criaLista(int max)
{
    int i=0, *copy_lista;
    int *elem = (Node*) malloc(sizeof(Node));

    copy_lista = elem;

    while(i < max)
    {
        *elem = i;
        *elem = (Node*) malloc(sizeof(Node));
        elem->prox=elem;
        i++;
    }
    elem = NULL;
    return copy_lista;
}

void mostra(int *lista)
{
    int i = 0;
    for(i=0 ; lista != NULL ; i++)
    {
        printf("lista[%d]=%d\n",i,*lista);
        lista = (lista)+(sizeof(int));
    }
}

int main()
{
    Node *lista;

    lista = criaLista(10);
    mostra(lista);
    return 0;
}
