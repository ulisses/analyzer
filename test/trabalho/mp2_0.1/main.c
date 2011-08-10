#include "all.h"

int main()
{
	Grafo *g;
	AvlRuas *lr = NULL;
	AvlPontosInteresse *lpi=NULL;
	LLRuas *ll=NULL;
	
	g = carregaRuas(&lr, &lpi);
	gravaRuas(lr,lpi);
	
	return 0;
}
