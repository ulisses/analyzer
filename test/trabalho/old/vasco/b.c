#include "b.h"

bool ePontoTuristico(char *tipo)
{
	return (strcasecmp(tipo,"igreja")==0 || strcasecmp(tipo,"teatro")==0
	     || strcasecmp(tipo,"pontoturismo")==0 || strcasecmp(tipo,"museu")==0
	     || strcasecmp(tipo,"monumento")==0
	     );
}

ListaPontosInteresse * addListaPontosInteresse (Ponto * ponto, ListaPontosInteresse * lpi)
{
    if (lpi == NULL)
    {
          lpi = (ListaPontosInteresse *) malloc(sizeof(ListaPontosInteresse));
          lpi->nome = ponto->nome;
          lpi->ponto = ponto;
          lpi->prox = NULL;

          return lpi;
    }

    ListaPontosInteresse * auxlpi = (ListaPontosInteresse *) malloc(sizeof(ListaPontosInteresse));

    auxlpi->nome = ponto->nome;
    auxlpi->ponto=ponto;
    auxlpi->prox=lpi;
    
    return auxlpi;
}

ListaRuas * addListaRua(Rua * rua, ListaRuas * lr)
{
	if (lr == NULL)
	{
		lr = (ListaRuas *) malloc(sizeof(ListaRuas));
		lr->nomeRua = rua->nome;
		lr->rua = rua;
		lr->prox = NULL;
		
		return lr;
	}
	
	ListaRuas *aux = (ListaRuas *) malloc(sizeof(ListaRuas));
	
	aux->nomeRua = rua->nome;
	aux->rua = rua;
	aux->prox = lr;
	
	return aux;
}

Rua *novaRua(char *nome, Key limite1, Key limite2, float comp, float tempo, ListaRuas ** lr)
{
	Rua *rua = (Rua *) malloc(sizeof(Rua));
	
	rua->nome=nome;
	rua->limite1=limite1;
	rua->limite2=limite2;
	rua->comprimento=comp;
	rua->tempoMedio=tempo;
	rua->listaPontos=NULL;
	
	(*lr)=addListaRua(rua,*lr);
	
	return rua;
}

Ponto* novoPonto (Ponto * ponto,char *nome, char *descricao, Key limite1, float distancia, int valorHistorico, int valorPaisagistico, int valorComercial,  int valorArquitectonico, bool pontoTuristico, float tempoMedio,Rua* rua, ListaPontosInteresse ** lpi)
{
	if(ponto == NULL)
	{
		Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
		rua->listaPontos = ponto;
		ponto->nome=nome;
		ponto->descricao=descricao;
		ponto->limite1=limite1;
		ponto->distancia=distancia;
		ponto->tempoMedio=tempoMedio;
		ponto->valorHistorico=valorHistorico;
		ponto->valorPaisagistico=valorPaisagistico;
		ponto->valorComercial=valorComercial;
		ponto->valorArquitectonico=valorArquitectonico;
		ponto->pontoTuristico=pontoTuristico;
		ponto->rua=rua;
		ponto->prox = NULL;

		rua->valorComercial=rua->valorComercial+valorComercial;
		rua->valorHistorico=rua->valorHistorico+valorHistorico;
		rua->valorPaisagistico=rua->valorPaisagistico+valorPaisagistico;
		rua->valorArquitectonico=rua->valorArquitectonico+valorArquitectonico;
		
		*lpi = addListaPontosInteresse(ponto,*lpi);
		
		return ponto;
	}
	
	Ponto *aux = (Ponto *) malloc(sizeof(Ponto));
	
	aux->nome=nome;
	aux->descricao=descricao;
	aux->limite1=limite1;
	aux->distancia=distancia;
	aux->tempoMedio=tempoMedio;
	aux->valorHistorico=valorHistorico;
	aux->valorPaisagistico=valorPaisagistico;
	aux->valorComercial=valorComercial;
	aux->valorArquitectonico=valorArquitectonico;
	aux->pontoTuristico=pontoTuristico;
	aux->rua=rua;
	aux->prox = ponto;
	
	rua->listaPontos=aux;
	rua->valorComercial=rua->valorComercial+valorComercial;
	rua->valorHistorico=rua->valorHistorico+valorHistorico;
	rua->valorPaisagistico=rua->valorPaisagistico+valorPaisagistico;
	rua->valorArquitectonico=rua->valorArquitectonico+valorArquitectonico;
	
	*lpi = addListaPontosInteresse(aux,*lpi);
	return aux;
}

Grafo *insereRua(Grafo *grafo, Rua *rua)
{
	if(grafo->vertices[rua->limite1]==NULL)
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=NULL;
		grafo->vertices[rua->limite1]=aresta;
	}
	else
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=grafo->vertices[rua->limite1];
		grafo->vertices[rua->limite1]=aresta;
	}
	
	if(grafo->vertices[rua->limite2]==NULL)
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=NULL;
		grafo->vertices[rua->limite2]=aresta;
	}
	else
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=grafo->vertices[rua->limite2];
		grafo->vertices[rua->limite2]=aresta;
	}
	
	return grafo;
}

Grafo *criaGrafo(int size)
{
	Grafo *g = (Grafo *) malloc(sizeof(Grafo));
	int i;
	
	g->size=size;
	*g->vertices = (Arestas *) malloc(size*sizeof(Arestas));
	
	for(i=0 ; i<size ; i++)
	{
		g->vertices[i]=NULL;
	}
	
	return g;
}

Rua * procuraRua(char * nomeRua, ListaRuas *lr)
{
	ListaRuas *aux = lr;
	for(;aux!=NULL && strcasecmp(nomeRua,aux->nomeRua)<0;aux=aux->prox);
	return aux->rua;

}

Grafo *carregaGrafo(ListaRuas **lr, ListaPontosInteresse **lpi, char *file)
{
	FILE *fp = fopen(file,"r");
	int nrRuas,nrArestas, nrVertices, i,nodo1,nodo2,valorArquitectonico, valorPaisagistico, valorHistorico, valorComercial, limite1;
	float tempoMedio, distancia, distanciaPonto, tempoMedioPonto;
	char *linha=(char *)malloc(sizeof(char));
	char *nomeRua=(char *)malloc(sizeof(char));
	char *nomePontoInteresse=(char *)malloc(sizeof(char));
	char *tipo=(char *)malloc(sizeof(char));
	char *descricao=(char *)malloc(sizeof(char));
	
	fscanf(fp, "Ruas:%d%*c", &nrRuas);
	
	fscanf(fp, "Vertices:%d%*c", &nrVertices);
	
	fscanf(fp, "Arestas:%d%*c", &nrArestas);
	
	Grafo* g = criaGrafo(nrVertices);
	
	for(i=0 ; i < nrArestas ; i++)
	{
		fscanf(fp, "%[^\n]%*c", linha);
		sscanf(strtok(linha,"-"),"%d",&nodo1);
		sscanf(strtok(NULL," "),"%d",&nodo2);
		nomeRua = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%f",&distancia);
		sscanf(strtok(NULL,":"),"%f",&tempoMedio);
		
		g = insereRua(g, novaRua(strdup(nomeRua),nodo1,nodo2,distancia,tempoMedio,lr));
	}
	
	fscanf(fp, "%[^\n]%*c", linha);
	
	for( ; fscanf(fp, "%[^\n]%*c", linha) != EOF ; )
	{
		nomePontoInteresse = strtok(linha,":");
		tipo = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%d",&valorArquitectonico);
		sscanf(strtok(NULL,":"),"%d",&valorPaisagistico);
		sscanf(strtok(NULL,":"),"%d",&valorHistorico);
		sscanf(strtok(NULL,":"),"%d",&valorComercial);
		descricao = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%d",&limite1);
		sscanf(strtok(NULL,":"),"%f",&distanciaPonto);
		sscanf(strtok(NULL,":"),"%f",&tempoMedioPonto);
		nomeRua = strtok(NULL,":");
		
		Rua *rua = procuraRua(strdup(nomeRua), *lr);
		
		novoPonto(rua->listaPontos,strdup(nomePontoInteresse), strdup(descricao), limite1,
			distanciaPonto, valorHistorico, valorPaisagistico, valorComercial,
			valorArquitectonico, ePontoTuristico(tipo), tempoMedioPonto, rua, lpi);
	}
	return g;
}

char *showTipo(TipoPontoInteresse tipo)
{
	char *tip = (char *) malloc(sizeof(char));
	
	switch(tipo) {
		case(Restaurante): {
			tip = strdup("restaurante"); return tip;
		}
		case(Igreja): {
			tip = strdup("igreja"); return tip;
		}
		case(Cinema): {
			tip = strdup("cinema"); return tip;
		}
		case(Teatro): {
			tip = strdup("teatro"); return tip;
		}
		case(Shopping): {
			tip = strdup("shopping"); return tip;
		}
		case(Hotel): {
			tip = strdup("hotel"); return tip;
		}
		case(PontoTurismo): {
			tip = strdup("pontoturismo"); return tip;
		}
		case(Museu): {
			tip = strdup("museu"); return tip;
		}
		case(Jardim): {
			tip = strdup("jardim"); return tip;
		}
		case(Monumento): {
			tip = strdup("monumento"); return tip;
		}
		case(Farmacia): {
			tip = strdup("farmacia"); return tip;
		}
		case(Hospital): {
			tip = strdup("hospital"); return tip;
		}
		case(Correios): {
			tip = strdup("correios"); return tip;
		}
		case(Cafe): {
			tip = strdup("cafe"); return tip;
		}
	}
	return tip;
}

void gravaGrafo(Grafo *grafo, char *nomeFile, ListaPontosInteresse *lpi)
{
	FILE *fp = fopen(nomeFile,"w");
	int nrRuas=0, nrVertices, nrArestas, i;
	Rua *rua;
	Ponto *ponto;
	
	fprintf(fp,"Ruas:%d\n",nrRuas);
	
	fprintf(fp,"Vertices:%d\n",nrVertices);
	fprintf(fp,"Arestas:%d\n",nrArestas);
	
	for(i=0 ; i < grafo->size ; i++)
	{
		for( ; grafo->vertices[i] != NULL ; grafo->vertices[i] = grafo->vertices[i]->prox)
		{
			rua = grafo->vertices[i]->rua;
			fprintf(fp, "%d-%d %s:%f:%f\n",rua->limite1, rua->limite2, rua->nome, rua->comprimento, rua->tempoMedio);
		}
	}
	fprintf(fp,"Pontos:\n");
	
	for( ; lpi != NULL; lpi = lpi->prox)
	{
		ponto = lpi->ponto;
		
		fprintf(fp, "%s:%s:%d:%d:%d:%d:%s:%d:%f:%f:%s\n", ponto->nome, showTipo(ponto->tipo), ponto->valorArquitectonico,
		        ponto->valorPaisagistico, ponto->valorHistorico, ponto->valorComercial, ponto->descricao, ponto->limite1,
		        ponto->distancia, ponto->tempoMedio, ponto->rua->nome);
	}
/*	
		nomePontoInteresse = strtok(linha,":");
		tipo = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%d",&valorArquitectonico);
		sscanf(strtok(NULL,":"),"%d",&valorPaisagistico);
		sscanf(strtok(NULL,":"),"%d",&valorHistorico);
		sscanf(strtok(NULL,":"),"%d",&valorComercial);
		descricao = strtok(NULL,":");
		sscanf(strtok(NULL,":"),"%d",&limite1);
		sscanf(strtok(NULL,":"),"%f",&distanciaPonto);
		sscanf(strtok(NULL,":"),"%f",&tempoMedioPonto);
		nomeRua = strtok(NULL,":");*/

}

int main()
{
	Grafo *g=NULL;
	ListaRuas *lr = NULL;
	ListaPontosInteresse *lpi=NULL;
	
	g = carregaGrafo(&lr, &lpi,"b.txt");
	
	printf("g=%s\n",g->vertices[1]->rua->nome);
	printf("g=%s\n",g->vertices[1]->rua->listaPontos->descricao);
	printf("g=%s\n",g->vertices[1]->rua->listaPontos->prox->descricao);
	printf("g=%s\n",g->vertices[1]->rua->listaPontos->prox->prox->descricao);
	
	printf("||=%s\n",lr->nomeRua);
	printf("||=%s\n",lr->prox->nomeRua);
	
	printf("LPI=%s\n",lpi->nome);
	printf("LPI=%s\n",lpi->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->prox->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->prox->prox->prox->nome);
	
	gravaGrafo(g, "b.1.txt",lpi);
	
/*	Rua *rua=NULL;
	Rua *rua1=NULL;
	ListaRuas *lr = NULL;
	Ponto * ponto = NULL;
	Ponto * ponto1 = NULL;
	ListaPontosInteresse * lpi = NULL;
	
	rua1 = novaRua(strdup("A25"),1,2,9.0,9.1,&lr);
	rua  = novaRua(strdup("rua1"),3,2,9.0,9.1,&lr);
	
	ponto = novoPonto(ponto,strdup("museu"), strdup("lindo"),2,1.2,3,4,5,6,false,1.7,rua,&lpi);
	ponto = novoPonto(ponto,strdup("igreja"), strdup("bonito"),1,1.2,1,2,3,4,false,1.4,rua,&lpi);
	
	int i;
	
	for(i=0 ; i < 2 ; i++)
	{
		novaRua(strdup("rua1"),i,2,9.0,9.1,&lr);
	}
	
	ponto1 = novoPonto(ponto,strdup("m22useu"), strdup("lindo2"),2,1.2,3,4,5,6,false,1.7,rua1,&lpi);
	ponto1 = novoPonto(ponto,strdup("muse33u"), strdup("lindo1"),2,1.2,3,4,5,6,false,1.7,rua1,&lpi);
	
	printf("lr=%s\n",lr->nomeRua);
	printf("lr=%s\n",lr->prox->nomeRua);
	printf("lr=%s\n",lr->prox->prox->nomeRua);
	printf("lr=%s\n",lr->prox->prox->prox->nomeRua);*/
	
/*	printf("lr=%d\n",lr->rua->limite1);
	printf("lr=%d\n",lr->prox->rua->limite1);
	printf("lr=%d\n",lr->prox->prox->rua->limite1);
	printf("lr=%d\n",lr->prox->prox->prox->rua->limite1);
	
	printf("lpi=%s\n",lpi->nome);
	printf("lpi=%s\n",lpi->prox->nome);
	printf("lpi=%s\n",lpi->prox->prox->nome);
	printf("lpi=%s\n",lpi->prox->prox->prox->nome);
	*/
/*	printf("ponto->descricao= %s\n",rua->listaPontos->nome);
	printf("ponto->descricao= %f\n",rua->listaPontos->prox->distancia);
	printf("lpi->nome %s\n",lpi->nome);
	printf("lpi->->proz->nome %s\n",lpi->prox->nome);
	printf("lista->nome= %s\n",lr->nomeRua);
	printf("lista->prox->nome= %s\n",lr->prox->nomeRua);
	printf("rua->nome= %s\n",rua->nome);
	printf("rua->comprimento=>%F<\n",rua->comprimento);
	puts("----------");
	*/
	//carregaRuas();
	
	
	
	return 0;
}
