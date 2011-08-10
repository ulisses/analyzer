#include <stdbool.h>

typedef struct {
	bool comercio;
	float comprimento;
	float tempoMedio;
	char valorArquitectonico; //0-20\
	Local* locaisDeInteresse; //apontador para uma estrutura p representar os Locais, ainda nao sei que por
}InfoRua;

// typedef struct structRua {
// 	InfoRua* info;
// 	Cruzamento* ponta;
// 	struct structRua* proxima; // cada vértice(cruzamento) tem uma lista ligada de ruas(arcos) que lhe estão ligados
// }Rua, Arco;
// 
// typedef struct structCruzamento {
// 	int valencia;
// 	struct structCruzamento* proximo; // por causa da lista de adjacencia, cdada grafo tem uma [Vertices*]
// 	Rua* ruas; 
// }Cruzamento, *Vertice;
// 
// typedef struct {
//     long nCruzamentos, nRuas;
//     Vertice* listaAdj; // grafo->vertices = (Vertex*) malloc(n_cruzamentos * sizeof(Cruzamento*));
// } Grafo;

//////////////////////////////////////////////////////////////////

typedef struct {
	InfoCruzamento *infoCruzamento;
	Rua *rua;
}Cruzamento;

typedef struct rua { // todas as ruas adjacentes a um cruzamento
	InfoRua *infoRua;
	Cruzamento *cruzamento; // o cruzamento final da rua
	struct rua *prox;
}Rua;

typedef Graph *Cruzamento[999];
