/**

    @file      Biblioteca.h
    @brief     
    @details   
    @author    Jo�o Barbosa
    @date      22.05.2024
    @copyright Jo�o Barbosa, 2024. All right reserved.

**/
#pragma once

#pragma once
#include <stdio.h>
#include <stdlib.h>
#include "stdbool.h"
#include <string.h>

#define MAXCHAR 100
#pragma warning(disable: 4996)

typedef struct Adjacencias {
    int id;	                         /**< Identificador do v�rtice de destino da aresta. */
    int peso;                        /**< Peso da aresta. */
    struct Adjacencias* next;        /**< Apontador para a pr�xima aresta na lista de adjac�ncias. */
}Adjacencias;


typedef struct Vertices {
    int id;                          /**< Identificador do v�rtice. */
    Adjacencias* proxAdj;            /**< Apontador para a lista de adjac�ncias do v�rtice. */
    struct Vertices* proxVertice;    /**< Apontador para o pr�ximo v�rtice na lista de v�rtices. */
} Vertices;


typedef struct Grafo {
    Vertices* inicioGrafo;            /**< Apontador para o in�cio da lista de v�rtices do grafo. */
} Grafo;



#pragma region Vertices 

Vertices* CriaVertice(int id);
bool ExisteVertice(Vertices* inicio, int id);
Vertices* InsereVertice(Vertices* vertices, Vertices* novo, bool* res);
Vertices* OndeEstaVertice(Vertices* inicio, int id);
void destroiAdjacencias(Adjacencias* destroir);
Adjacencias* EliminaAllAdj(Adjacencias* listaAdjacencias, bool* res);
Adjacencias* EliminaAdj(Adjacencias* listaAdjacencias, int codAdj, bool* res);
Vertices* EliminaVertice(Vertices* vertices, int codVertice, bool* res);
Vertices* EliminaAdjacenciaVertices(Vertices* vertices, int codAdj, bool* res);

#pragma endregion


#pragma region Arestas

Adjacencias* NovaAdjacencia(int id, int peso);
Adjacencias* InsereAdj(Adjacencias* listaAdja, int idDestino, int peso);
void DestroiAdjacencia(Adjacencias* ptAdjacent);
Adjacencias* EliminaTodasAdjacencias(Adjacencias* listAdj, bool* res);

#pragma endregion 

#pragma region Grafo
Grafo* CriaGrafo();
bool ExisteVerticeGrafo(Grafo* g, int idVertice);
Grafo* InsereVerticeGrafo(Grafo* g, Vertices* novo, int* res);
Vertices* OndeEstaVerticeGrafo(Grafo* g, int idVertice);
Grafo* EliminaVerticeGrafo(Grafo* g, int codVertice, bool* res);
Grafo* EliminaAdjGrafo(Grafo* g, int origem, int destino, bool* res);
Grafo* InsereAdjacenciasGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* res);
void MostrarGrafo(Vertices* grafo);

#pragma endregion

Grafo* carregarMatrizParaGrafo(char fileName[], int* numLinhas, int* numColunas);
bool GuardaGrafoBinario(Grafo* grafo, char fileName[]);
int CarregaGrafoBinario(char fileName[]);
Grafo* ProcuraProfundidadeRec(Grafo* g, int origem, int destino, bool* visitado, int* caminho, int indice, int* somaCaminhos);
Grafo* ProcuraProfundidade(Grafo* g, int origem, int destino, int numVertices, int* soma);
Grafo* DFSrec(Grafo* g, int origem, int destino, bool* visitado, int* caminho, int indice, int* somaCaminhos, int* somaMaxima, int* caminhoMaximo, int numVertices);
void encontrarCaminhoMaiorSoma(Grafo* g, int origem, int destino, int numVertices);
