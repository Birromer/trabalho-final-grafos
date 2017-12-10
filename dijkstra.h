#define MAXNODOS 100
#define INFINITO 32768


int inicializaGrafo(int grafo[MAXNODOS][MAXNODOS]);

int nodoFechado(int y, int fechado[MAXNODOS], int o);

int salvaGrafo(char *nomeArq, int grafo[MAXNODOS][MAXNODOS], int *n);

void atualizaDist(int matrizAdj[MAXNODOS][MAXNODOS], int setAberto[MAXNODOS], int setFechado[MAXNODOS], int o, int dist[MAXNODOS], int x, int nNodos);

int menorAberto(int setFechado[MAXNODOS], int dist[MAXNODOS], int n, int o);

void imprimeClosedSet(int ClosedSet[MAXNODOS], int O);

void imprimeOpenSet(int OpenSet[MAXNODOS], int distancias[MAXNODOS]);

int dijkstra(int x, int y, char *nomeArq, int op);
