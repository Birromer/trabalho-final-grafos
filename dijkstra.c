#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"
#define MAXNODOS 100
#define INFINITO 32768


int inicializaGrafo(int grafo[MAXNODOS][MAXNODOS])
/*recebe a matriz de ajacencia e inicializa todos valores com 0*/

{
    int i, j;

    for (i=0; i<MAXNODOS; i++)
    {
        for(j=0; j<MAXNODOS; j++)
        {
            grafo[i][j] = INFINITO; //inicializa com infinito todo o grafo
        }
    }
    return 1;
}

/*verifica se y esta ou nao no conjunto fechado para encerrar a aplicacao*/
int nodoFechado(int y, int fechado[MAXNODOS], int o)
{
    int i=0;

    while(i<o) //enquanto houver nodos
    {
        if(fechado[i] == y)
            return 1;       //y ja esta no conjunto fechado

        i++;
            //printf(" - %d -", fechado[i]);
    }
    return 0;               //y ainda nao esta no conjunto fechado
}

int salvaGrafo(char *nomeArq, int grafo[MAXNODOS][MAXNODOS], int *n)
/*recebe o nome doa arquivo, a matriz de ajacencia e um ponteiro para onde armazenar o numero de vertices
insere na matriz o peso das arestas e retorna 1 caso a funcao encerre normalmente e 0 caso de erro em algum processo com o arquivo*/
{
    FILE *arq;
    int x, y, p, i, vertices, arestas;

    if (! (arq = fopen(nomeArq, "r")) )
    {
        printf("Erro na abertura do arquivo %s", nomeArq);
        return 0;
    }
    else
    {
        if (! (fscanf (arq, "%d %d\n", &vertices, &arestas)) )
        {
            printf("Erro na leitura das dimensoes do grafo no arquivo %s", nomeArq);
            return 0;
        }
        else
        {
            //printf("%d vertices e %d arestas\n\n", vertices, arestas);
            *n = vertices;

            for (i=1; i<=arestas; i++)
            {
                if (! (fscanf(arq, "%d %d %d\n", &x, &y, &p)) )
                {
                    printf("Erro na leitura do arquivo %s", nomeArq);
                    return 0;
                }
                else
                {
                    //printf("vertice %d conectado no vertice %d com peso %d\n", x, y, p);

                    grafo[x][y] = p;
                    grafo[y][x] = p;
                }
            }
        }
        fclose(arq);
    }
    return 1;
}

/*recebe o grafo, o conjunto aberto para atualizacao, o fechado para verificacao, a quantidade de nodos no conjunto fechado, as distancias, o nodo atual e a quantidade de nodos no grafo*/
void atualizaDist(int matrizAdj[MAXNODOS][MAXNODOS], int setAberto[MAXNODOS], int setFechado[MAXNODOS], int o, int dist[MAXNODOS], int x, int nNodos)
{
    int i, aux=0;

    for(i=0; i<nNodos; i++) //percorre os nodos adjacentes ao nodo atual
    {
        if(matrizAdj[x][i] != INFINITO) //quando encontra um nodo adjacente
        {
            if(!nodoFechado(i, setFechado, o))//verifica se esse nodo nao esta no conjunto fechado
            {
                //coloca o nodo adjacente no set aberto
                setAberto[i] = 1;

                aux = dist[x] + matrizAdj[x][i]; //soma a distancia do nodo atual ate x mais o peso da nova aresta
                if(aux < dist[i]) //se for menor que a distancia do nodo adjacente ate x na lista...
                    dist[i] = aux; //... atualiza a distancia
            }
        }
    }
}

/*recebe o set aberto, a quantidade de nodos no set aberto e a tabela com distancias para x*/
int menorAberto(int setFechado[MAXNODOS], int dist[MAXNODOS], int n, int o)
{
    int menor = 0, aux = INFINITO, i;

    for (i=0; i<n; i++)
    {
        if(nodoFechado(i, setFechado, o)) //se estivr no fechado, ignora
        {
            ;
        }
        else if(dist[i] < aux && !nodoFechado(i, setFechado, o)) //se a distancia for menor e nao estiver no fechado
        {
            aux = dist[i]; //atualiza distancia minima
            menor = i; //atualiza nodo com menor distancia
        }
    }

    return menor; //retorna nodo com menor distancia
}

void imprimeClosedSet(int ClosedSet[MAXNODOS], int O)
{
    int i=0;
    printf("Conjunto Fechado S:\n");
    for(i=0;i<O;i++)
    {
            printf(" %d -", ClosedSet[i]);
    }
    printf("\n");
}

void imprimeOpenSet(int OpenSet[MAXNODOS], int distancias[MAXNODOS])
{
    int i=0;
    printf("\nConjunto Aberto:\n");
    printf("======================================================================\n");
    printf("\tNODO \t||\tDISTANCIA\n");
    printf("======================================================================\n");
    for(i=0;i<MAXNODOS;i++)
        {
            if(OpenSet[i]==1)
                printf("\t%d\t||\t%d\n", i , distancias[i]);
        }
    printf("======================================================================\n");

}

int dijkstra(int x, int y, char *nomeArq, int op) //nodos de entrada cuja menor distancia deve ser calculada, nome do arquivo com o grafo; x eh o nodo inicial
{
    int grafo[MAXNODOS][MAXNODOS];
    /*conjunto fechado nao esta organizado conforme o numero dos nodos, apenas na ordem em que entraram no conjunto*/
    int fechado[MAXNODOS]={};
    /*conjunto aberto*/
    int aberto[MAXNODOS]={};
    /*as distancias estao organizadas de acordo com o numero do respectivo nodo*/
    int distancias[MAXNODOS];//vetor que guarda as distancias para x
    /*quantidade de nodos; auxiliar; nodo atual*/
    int vertices=0, i=0, atual;
    /*quantidade de nodos no conjunto fechado*/
    int o=0;
    /*usado para terminar o while*/
    int fim=0;

    if(inicializaGrafo(grafo))
    {
        if(salvaGrafo(nomeArq, grafo, &vertices))
        {
            /*inicializa vetor de distancias*/
            for(i=0; i<MAXNODOS; i++)
                distancias[i]=INFINITO;

            i=0; //reseta contador
            atual = x; //inicializa com o nodo inicial

            distancias[atual]=0;//inicializa distancia do nodo inicial

            while(!fim && i<vertices)//enquanto y nao esta em fechado
            {
                if (op == 2)
                {
                    printf("\n\n\n");
                    printf("\t-->Passo %d\n", i+1);
                    printf("\nNodo Visitado: %d \n", atual);
                    printf("\nDistancia ate a origem: %d\n\n", distancias[atual]);
                }

                atualizaDist(grafo, aberto, fechado, o, distancias, atual, vertices);
                //fecha o nodo
                fechado[o]=atual;
                o++;

                if(op == 2)
                {
                    imprimeClosedSet(fechado, o);
                }
                //escolhe o menor nodo adjacente
                aberto[atual] = 0;
                if (op ==2)
                {
                    imprimeOpenSet(aberto, distancias);
                }
                atual = menorAberto(fechado, distancias, vertices, o);
                fim = nodoFechado(y, fechado, o);//verifica se y ja esta no conjunto fechado
                i++;

           }

        return distancias[y]; //retorna distancia do nodo procurado a origem
        }
        else
            return 0;
    }
    else return 0;
}

