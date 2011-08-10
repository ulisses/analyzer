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
	if(grafo->vertices[rua->limite1]->aresta==NULL)
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=NULL;
		grafo->vertices[rua->limite1]->aresta=aresta;
	}
	else
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=grafo->vertices[rua->limite1]->aresta;
		grafo->vertices[rua->limite1]->aresta=aresta;
	}
	
	if(grafo->vertices[rua->limite2]->aresta==NULL)
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=NULL;
		grafo->vertices[rua->limite2]->aresta=aresta;
	}
	else
	{
		Arestas* aresta = (Arestas *) malloc(sizeof(Arestas));
		aresta->rua = rua;
		aresta->prox=grafo->vertices[rua->limite2]->aresta;
		grafo->vertices[rua->limite2]->aresta=aresta;
	}
	
	return grafo;
}

Grafo *criaGrafo(int size)
{
	Grafo *g = (Grafo *) malloc(sizeof(Grafo));
	int i;
	
	g->size=size;
	
	*g->vertices = (Vertices *) malloc (size*sizeof(Vertices));
	
	for(i=0 ; i<=size ; i++)
	{
	    g->vertices[i]=(Vertices *) malloc(sizeof(Vertices));
	    g->vertices[i]->cor=WHITE;
		g->vertices[i]->aresta=NULL;
	}
	 g->vertices[i]=NULL;
	
	return g;
}

Rua * procuraRua(char * nomeRua, ListaRuas *lr)
{
	ListaRuas *aux = lr;
	for(;aux!=NULL && strcasecmp(nomeRua,aux->nomeRua)<0;aux=aux->prox);
	return aux->rua;

}

Grafo *carregaRuas(ListaRuas **lr, ListaPontosInteresse **lpi)
{
	FILE *fp = fopen("b.txt","r");
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


FIFO *acrescentaFIFO(Vertices *vertice, FIFO **fifo)
{
    FIFO *aux1 = *fifo;

    if(aux1->vertice == NULL)
    {
        aux1->vertice = vertice;
        aux1->prox = NULL;

        *fifo = aux1;
    }
    else
    {
        FIFO * aux = (FIFO *) malloc (sizeof(FIFO));

        aux->vertice = vertice;
        aux->prox = *fifo;
        *fifo = aux;
    }

    return *fifo;
}

FIFO* criaFIFO ()
{
	FIFO * fifo = (FIFO *) malloc(sizeof(FIFO));
	fifo->vertice = NULL;
	fifo->prox = NULL;
	
	return fifo;
}

FIFO * adjVer(int vertice, Grafo * grafo)
{
	FIFO * adjacentes = criaFIFO();
	Grafo * g = grafo;

	for(;g->vertices[vertice]->aresta != NULL; g->vertices[vertice]->aresta = g->vertices[vertice]->aresta->prox)
	{
		if(g->vertices[vertice]->aresta->rua->limite1 == vertice)
			adjacentes=acrescentaFIFO(g->vertices[g->vertices[vertice]->aresta->rua->limite2], &adjacentes);
		else
			adjacentes=acrescentaFIFO(g->vertices[g->vertices[vertice]->aresta->rua->limite1], &adjacentes);
	}
	
	return adjacentes;
}

int numVerAdj(Vertices * ver, int vertice)
{
	int adjacente;
	A
	if (ver->aresta->rua->limite1 == vertice)
	{
		adjacente = ver->aresta->rua->limite2;
	}
	else
	{
		adjacente = ver->aresta->rua->limite1;
	}
	A
	return adjacente;
}

bool isEmpty(FIFO *fifo)
{
    if(fifo == NULL || (fifo->vertice == NULL && fifo->prox==NULL))
        return true;
    else
        return false;
}

Vertices * removeFIFO(FIFO **fifo)
{
        FIFO* aux = *fifo;
        Vertices * vertice = (Vertices *) malloc (sizeof(Vertices));

        if (aux->prox == NULL)
        {

            vertice->aresta=(*fifo)->vertice->aresta;
            vertice->cor=(*fifo)->vertice->cor;

            (*fifo)->vertice = NULL;
            (*fifo)->prox = NULL;
A
            return vertice;
        }

        FIFO* aux1 = *fifo;
        A
        for(;aux->prox!=NULL;aux=aux->prox)
        {
               aux1 = aux;
        }

        vertice->aresta = aux->vertice->aresta;
        vertice->cor=aux->vertice->cor;
        aux1->prox=NULL;
        aux =NULL;

        return vertice;
}

void PesquisaLargura(Grafo *g, int vertice)
{
    FIFO * fifo = criaFIFO(), *adjacentes;
    int i, d[g->size], adjacente,j, ver;
    Vertices * parente[g->size], *firstOut;

    for(i=0; i<=g->size;i++)
    {
        g->vertices[i]->cor = WHITE;
        parente[i] = NULL;
    }

    d[vertice] = 0;
    g->vertices[vertice]->cor = GRAY;

    fifo = acrescentaFIFO(g->vertices[vertice], &fifo);

    while(!isEmpty(fifo))
    {
        firstOut=removeFIFO(&fifo);
A
	printf("firstout %d\n",firstOut->aresta->rua->limite1);

        if(j==0)
        {
            ver = vertice;
            adjacentes = adjVer(ver, g); 
        }
        else
        {
            ver = numVerAdj(firstOut,ver);
            adjacentes = adjVer(ver, g); 
        }
         printf("vertice %d\n",ver);
A
        for(; adjacentes->prox!=NULL; adjacentes=adjacentes->prox)
        {
                if (adjacentes->vertice->cor == WHITE)
                {
                    A
                    adjacente = numVerAdj(firstOut, ver);
                    adjacentes->vertice->cor = GRAY;
                    d[adjacente] = d[ver] +1;
                    parente[adjacente] = adjacentes->vertice;
                    fifo = acrescentaFIFO(adjacentes->vertice,&fifo);
                }
        }

        if (adjacentes->prox == NULL)
        {
            A
            if (adjacentes->vertice != NULL)
            {
                A
                adjacente = numVerAdj(firstOut, vertice);
                adjacentes->vertice->cor = GRAY;
                d[adjacente] = d[vertice] +1;
                parente[adjacente] = adjacentes->vertice;
                acrescentaFIFO(adjacentes->vertice,&fifo);
            }
        }
        A
        j++;
        firstOut->cor = BLACK;

        firstOut = NULL; 
    }
}

int main()
{
	Grafo *g;
	ListaRuas *lr = NULL;
	ListaPontosInteresse *lpi=NULL;

	g = carregaRuas(&lr, &lpi);

	printf("g=%s\n",g->vertices[1]->aresta->rua->nome);
	printf("g=%s\n",g->vertices[1]->aresta->rua->listaPontos->descricao);
	printf("g=%s\n",g->vertices[1]->aresta->rua->listaPontos->prox->descricao);
	printf("g=%s\n",g->vertices[1]->aresta->rua->listaPontos->prox->prox->descricao);
	
	printf("||=%s\n",lr->nomeRua);
	printf("||=%s\n",lr->prox->nomeRua);
	
	printf("LPI=%s\n",lpi->nome);
	printf("LPI=%s\n",lpi->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->prox->prox->nome);
	printf("LPI=%s\n",lpi->prox->prox->prox->prox->prox->nome);
	
	//PesquisaLargura(g,4);
	
	return 0;
}
