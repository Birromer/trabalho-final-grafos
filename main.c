#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "dijkstra.h"
#define MAXNODOS 100
#define INFINITO 32768


int main(int argc, char *argv[])
{
    int grafo[MAXNODOS][MAXNODOS];  //matriz de adjacencia do grafo
    int x, y, op, vertices, distancia; //nodo inicial, nodo final, numero de certices e variavel para armazenar distancia

    if (argc != 2)    //tratamento da entrada e selecao do tipo de processamento
    {
        printf("Erro no numero de parametros, o programa deve ser executado como:\n./trabFinalGrafos.exe <arquivo_com_o_grafo.dat>");
        return 0;
    }
    else
    {
        printf("Digite o nodo inicial e o nodo final: ");   //pede para digitar nodo incial e nodo final
        scanf("%d %d", &x, &y);

        do
        {
            printf("Execucao:\n1 - Simples\n2 - Passo a passo\n"); //selecao do tipo de processamento
            scanf("%d", &op);
        } while(op != 1 && op != 2);

        distancia = dijkstra(x, y, argv[1], op);    //chamada do algoritimo com os nodos inicial e final, nome do arquivo e opcao de exibicao

        if (distancia == INFINITO)
        {
            printf("\n\n%d e %d nao estao conectados no grafo\n", x, y); //mensagem para o caso de nao existir conexao entre os nodos
        }
        else
        {
            printf("\n\nDistancia entre %d e %d = %d\n", x, y, distancia); //exibe distancia entre os nodos selecionados
        }
    }
    return 1;
}
