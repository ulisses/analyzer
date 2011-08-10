#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define A printf("|> %s %d\n",__FILE__ , __LINE__);

typedef int Key;

typedef enum {WHITE, GRAY, BLACK} Cor;

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

typedef struct ponto {
	char *nome; // nome do ponto de interesse
	TipoPontoInteresse tipo;
	int valorArquitectonico; // '0'-'9'
	int valorPaisagistico; // '0'-'9'
	int valorHistorico; // '0'-'9'
	int valorComercial; // '0'-'9'
	bool pontoTuristico;
	char *descricao; // descricao do ponto de interesse
	Key limite1;
	float distancia; // distancia do ponto de interesse ao cruzamento limite1
	float tempoMedio; // tempo medio desde o cruzamento limite1 ate ao ponto de interesse
	struct ponto * prox;
	struct rua * rua;
}Ponto;

// lista ligada com a informacao de todas as ruas
typedef struct rua {
	char *nome; // nome da rua
	Key limite1; // pontos (cruzamentos , vertices) que delimitam a rua
	Key limite2;
	float comprimento; // tamanho da rua
	float tempoMedio; // tempo medio a percorrer essa rua
	int valorArquitectonico; // '0'-'9'
	int valorPaisagistico; // '0'-'9'
	int valorHistorico; // '0'-'9'
	int valorComercial; // '0'-'9'
	Ponto *listaPontos; // pontos de interesse
}Rua;

typedef struct listaRuas {
    char * nomeRua;
    Rua * rua;
    struct listaRuas * prox;
} ListaRuas;

typedef struct listaPontosInteresse {
    char * nome;
    Ponto * ponto;
    struct listaPontosInteresse * prox;
} ListaPontosInteresse;

typedef struct aresta {
    Rua * rua;
    struct aresta * prox;
}Arestas;

typedef struct {
	Cor cor;
	Arestas *aresta;
}Vertices;

typedef struct vertices {
    int size;
    Vertices* vertices[];
} Grafo;

bool ePontoTuristico(char *tipo);
ListaPontosInteresse * addListaPontosInteresse (Ponto * ponto, ListaPontosInteresse * lpi);
ListaRuas * addListaRua(Rua * rua, ListaRuas * lr);
Rua *novaRua(char *nome, Key limite1, Key limite2, float comp, float tempo, ListaRuas ** lr);
Ponto* novoPonto (Ponto * ponto,char *nome, char *descricao, Key limite1, float distancia, int valorHistorico, int valorPaisagistico, int valorComercial,  int valorArquitectonico, bool pontoTuristico, float tempoMedio,Rua* rua, ListaPontosInteresse ** lpi);
Grafo *insereRua(Grafo *grafo, Rua *rua);
Grafo *criaGrafo(int size);
Rua * procuraRua(char * nomeRua, ListaRuas *lr);
Grafo *carregaGrafo(ListaRuas **lr, ListaPontosInteresse **lpi, char *file);
void gravaGrafo(Grafo *grafo, char *nomeFile, ListaPontosInteresse *lpi);
char *showTipo(TipoPontoInteresse tipo);
