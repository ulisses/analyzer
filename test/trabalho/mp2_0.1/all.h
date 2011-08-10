#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>

#define INF 999999999
#define A printf("|> %s %d\n", __FILE__, __LINE__);

typedef enum { WHITE
             , GRAY
             , BLACK
             } Cor;

typedef struct rua Rua;

typedef struct aresta {
	Rua * rua;
	struct aresta * prox;
}Arestas;

typedef struct grafo {
    int size;
    Arestas* vertices[];
} Grafo;

typedef enum {LB, EB, RB} BF;

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
	int limite1;
	float distancia; // distancia do ponto de interesse ao cruzamento limite1
	float tempoMedio; // tempo medio desde o cruzamento limite1 ate ao ponto de interesse
	struct ponto * prox;
	Rua * rua;
}Ponto;

typedef struct avlPontoInteresse {
	BF bf;
	char *nome;
	Ponto *ponto;
	struct avlPontoInteresse *left, *right;
}AvlPontosInteresse;

struct rua {
	char *nome; // nome da rua
	int limite1; // pontos (cruzamentos , vertices) que delimitam a rua
	int limite2;
	float comprimento; // tamanho da rua
	float tempoMedio; // tempo medio a percorrer essa rua
	int valorArquitectonico; // '0'-'9'
	int valorPaisagistico; // '0'-'9'
	int valorHistorico; // '0'-'9'
	int valorComercial; // '0'-'9'
	Ponto *listaPontos; // pontos de interesse
};

typedef struct llRuas {
	Rua *rua;
	struct llRuas *prox;
}LLRuas;

typedef struct avl {
	BF bf;
	char * nomeRua;
	LLRuas * ruas;
	struct avl *left, *right;
}AvlRuas;

typedef struct fifo {
    Arestas * aresta;
    struct fifo * prox;
} FIFO;

// ruas
AvlRuas *addRua(AvlRuas *tree, Rua *rua);
AvlRuas * addRuaAux(AvlRuas *tree, Rua * rua, bool *flag);
AvlRuas *rotateLeft(AvlRuas *tree);
AvlRuas *rotateRight(AvlRuas *tree);
void balanceFlags(AvlRuas *tree);
void inorderAVL(AvlRuas *tree);
Grafo *insereRua(Grafo *grafo, Rua *rua);
Rua *procuraRua(char *nomeRua, AvlRuas *tree);
Rua *novaRua(char *nome, int limite1, int limite2, float comp, float tempo, AvlRuas ** tree);
char *daNomeRua(char *nomeTroco);
LLRuas *insereRuaLL(LLRuas *ll, Rua *rua);
Rua *procuraRuaLL(char *nomeRua, LLRuas *ruas);
LLRuas *procuraRuaDaLL(char *nomeRua, AvlRuas *tree);

// pontos
bool ePontoTuristico(char *tipo);
Ponto *novoPonto (Ponto *ponto,char *nome, char *descricao, int limite1, float distancia, int valorHistorico, int valorPaisagistico, int valorComercial, int valorArquitectonico, bool pontoTuristico, float tempoMedio,Rua *rua, AvlPontosInteresse ** lpi, char * tipo);
AvlPontosInteresse *addPontosInteresse(Ponto *ponto, AvlPontosInteresse *tree);
AvlPontosInteresse *addPontosInteresseAux(AvlPontosInteresse *tree, Ponto *ponto, bool *flag);
AvlPontosInteresse *rotateLeftpi(AvlPontosInteresse *tree);
AvlPontosInteresse *rotateRightpi(AvlPontosInteresse *tree);
void balanceFlagspi(AvlPontosInteresse *tree);
TipoPontoInteresse daTipo(char *tipo);
AvlPontosInteresse *daPontos(TipoPontoInteresse tipo, AvlPontosInteresse *tree);
AvlPontosInteresse *daPontosAux(TipoPontoInteresse tipo, AvlPontosInteresse *tree, AvlPontosInteresse **treeAcc);
void inorderAVLpi(AvlPontosInteresse *tree);
char *setTipo(TipoPontoInteresse tipo);

// grafo
Grafo *criaGrafo(int size);
Grafo *carregaRuas(AvlRuas **lr, AvlPontosInteresse **lpi);
void PesquisaLargura(Grafo *g, int vertice, int * d, int * parentes, AvlPontosInteresse ** lpi);
void dijkstraMenor(Grafo * g, int vertice, float * peso, int * parentes);
AvlRuas * caminhoMaisCurto(int * parentes,int vertice, Grafo *g, AvlRuas * lr);
void gravaRuasAux(AvlRuas *lr, FILE *fp);
void gravaRuas(AvlRuas *tree, AvlPontosInteresse *treePts);
void gravaPontos(AvlPontosInteresse *tree, FILE *fp);

//fifo
FIFO *acrescentaFIFO(Arestas *aresta, FIFO * fifo);
FIFO *criaFIFO();
FIFO *adjVer(int vertice, Grafo * grafo);
bool isEmpty(FIFO *fifo);
FIFO *removeFIFO(FIFO *fifo, Grafo *g, int *vertice);

//misc
int numVerAdj(Arestas * aresta, int vertice);
int darVertice (Arestas * aresta, Grafo * g);
float daPeso(int aux,Arestas * arestas);
Rua * daRua(int vertice, Arestas * arestas);
float daTempo(AvlRuas *tree);
float daTempoAux(AvlRuas *tree, float *acc);
