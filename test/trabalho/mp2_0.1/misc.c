#include "all.h"

int numVerAdj(Arestas * aresta, int vertice)
{
    int adjacente;

    if (aresta->rua->limite1 == vertice)
    {
        adjacente = aresta->rua->limite2;
    }
    else
    {
        adjacente = aresta->rua->limite1;
    }

    return adjacente;
}

int darVertice (Arestas * aresta, Grafo * g)
{
        int i;

        if (g->vertices[aresta->rua->limite2] == aresta)
                i = aresta->rua->limite2;
        else
                i = aresta->rua->limite1;

        return i;
}

float daPeso(int aux,Arestas * arestas)
{
    float a=0;
    Arestas * aresta = arestas;
    for (;aresta != NULL; aresta = aresta->prox)
    {
        if (aresta->rua->limite1 == aux || aresta->rua->limite2 == aux)
        {
            a = aresta->rua->comprimento;
            break;
        }
    }
    return a;
}

Rua * daRua(int vertice, Arestas * arestas)
{
	Arestas * aresta = arestas;
	Rua * rua=NULL;

	for(;aresta!=NULL;aresta=aresta->prox)
	{
		if(aresta->rua->limite1 == vertice || aresta->rua->limite2 == vertice)
		{
			rua = aresta->rua;
			break;
		}
	}
	return rua;

}

// float daTempo(AvlRuas *tree)
// {
// 	float acc = 0;
// 	
// 	return(daTempoAux(tree,&acc));
// }
// 
// float daTempoAux(AvlRuas *tree, float *acc)
// {
// 	if(tree!=NULL)
// 	{
// 		*acc += tree->rua->tempoMedio;
// 		daTempoAux(tree->left,acc);
// 		daTempoAux(tree->right,acc);
// 	}
// 	return *acc;
// }
