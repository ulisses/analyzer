#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define A printf("|> %s %d\n",__FILE__ , __LINE__);

typedef int Key;
typedef enum { Restaurante
             , Igreja
             , Cinema
             , Teatro
             , Shopping
             , Hotel
             , PontoTurismo
             , Museu
             , Jardim
             , Monumento
             , Farmacia
             , Hospital
             , Correios
             , Cafe
             } TipoPontoInteresse;

typedef struct {
	char *nome; // nome do ponto de interesse
	TipoPontoInteresse tipo;
	char *descricao; // descricao do ponto de interesse
	Key limite1;
	float distancia; // distancia do ponto de interesse ao cruzamento limite1
	float tempoMedio; // tempo medio desde o cruzamento limite1 ate ao ponto de interesse
	Ponto *prox;
}Ponto;

// lista ligada com a informacao de todas as ruas
typedef struct rua {
	char *nome; // nome da rua
	Key limite1; // pontos (cruzamentos , vertices) que delimitam a rua
	Key limite2;
	float comprimento; // tamanho da rua
	float tempoMedio; // tempo medio a percorrer essa rua
	char valorArquitectonico; // '0'-'9'
	Ponto *listaPontos; // pontos de interesse
}Rua;

Ponto *novoPonto(char *nome, char *descricao, Key limite1, float distancia, float tempoMedio)
{
	Ponto *ponto = (Ponto *) malloc(sizeof(Ponto));
	if(ponto==NULL)
	{
		perror("ERROR: malloc");
		exit(EXIT_FAILURE);
	}
		
	ponto->nome=nome;
	ponto->descricao=descricao;
	ponto->limite1=limite1;
	ponto->distancia=distancia;
	ponto->tempoMedio=tempoMedio;
	
	return ponto;
}

void freePontos(Ponto **pontos)
{

}

/*
void freeRua(Rua **rua)
{
	Rua *aux;
	
	while(*rua)
	{
		aux=*rua;
		*rua=(*rua)->prox;
		free(aux->nome);
		free(aux);
	}
}
*/
void freeRua(Rua *rua)
{
	free(rua->nome);
	free(rua->listaPontos);
	free(rua);
	
	rua = NULL;
}

Rua *novaRua(Rua *rua, char *nome, Key limite1, Key limite2, float comp, float tempo, char valorArq/*, Ponto **pontos*/)
{
	if(rua == NULL)
	{
		rua = (Rua *) malloc(sizeof(Rua));
		if(rua == NULL)
		{
			perror("ERROR: malloc.");
			exit(EXIT_FAILURE);
		}
		
		rua->nome=nome;
		rua->limite1=limite1;
		rua->limite2=limite2;
		rua->comprimento=comp;
		rua->tempoMedio=tempo;
		rua->valorArquitectonico=valorArq;
		rua->listaPontos=NULL;
	}
	return rua;
}

int main()
{
	Rua *rua=NULL;
/*	Ponto **pontos = (Ponto **) malloc(sizeof(Ponto));
	int i;
	
	for(i=0 ; i < 10 ; i++)
		pontos[i] = (Ponto *) malloc(sizeof(Ponto));
	
	pontos[1]->nome=strdup("aa");
	
	printf("pontos[1]->nome=%s\n",pontos[1]->nome);
	*/
	rua = novaRua(rua,strdup("rua1"),11,22,9.0,9.1,'2');
	
/*	rua = novaRua(rua,strdup("rua2"),12,112,5.0,9.1,'9');
	
	rua = novaRua(rua,strdup("rua3"),123,112,5.1,9.1,'9');*/
	
	printf("rua->nome=>%s<\n",rua->nome);
	printf("rua->comprimento=>%F<\n",rua->comprimento);
	puts("----------");
/*	
	free(rua->nome);
	free(rua);*/
	
	//freeRua(rua);
	rua=NULL;
	
	if (rua == NULL)
		puts("null");
	else
		puts("not null");
	
	return 0;
}
