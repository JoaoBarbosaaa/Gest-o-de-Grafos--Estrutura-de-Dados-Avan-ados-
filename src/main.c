/**

    @file      main.c
    @brief     
    @details 
    @author    João Barbosa
    @date      22.05.2024
    @copyright © João Barbosa, 2024. All right reserved.

**/
#include <stdio.h>
#include <locale.h>
#include "Biblioteca.h"
#pragma comment(lib,"Bibliotecas.lib")


int main() {

	setlocale(LC_ALL, "Portuguese");
	
#pragma region Teste Funções
	int res;
	Grafo* Grafo1 = CriaGrafo();
	if (Grafo1 == NULL) {
		printf("Erro ao criar o grafo.\n");
	}
	else {
		printf("Grafo criado com sucesso.\n\n");
	}

	printf("Testes as funções\n\n");

	Vertices* novoVertice = CriaVertice(1);
	Grafo1 = InsereVerticeGrafo(Grafo1, novoVertice, &res);

	novoVertice = CriaVertice(0);
	Grafo1 = InsereVerticeGrafo(Grafo1, novoVertice, &res);

	novoVertice = CriaVertice(2);
	Grafo1 = InsereVerticeGrafo(Grafo1, novoVertice, &res);

	novoVertice = CriaVertice(3);
	Grafo1 = InsereVerticeGrafo(Grafo1, novoVertice, &res);

	novoVertice = CriaVertice(4);
	Grafo1 = InsereVerticeGrafo(Grafo1, novoVertice, &res);

	MostrarGrafo(Grafo1->inicioGrafo);
	printf("\n");

	printf("Insere vertice\n");
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 0, 1, 12, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 0, 4, 15, &res);

	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 1, 0, 343, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 1, 2, 121, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 1, 3, 243, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 1, 4, 0, &res);

	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 2, 1, 99, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 2, 3, 87, &res);

	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 3, 1, 67, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 3, 2, 11, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 3, 4, 82, &res);

	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 4, 0, 33, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 4, 1, 55, &res);
	Grafo1 = InsereAdjacenciasGrafo(Grafo1, 4, 3, 42, &res);


	MostrarGrafo(Grafo1->inicioGrafo);

	printf("------------------------------------------------------------------------------------\n");
	printf("Remove Adjacências\n");
	Grafo1 = EliminaAdjGrafo(Grafo1, 4, 3, &res);
	Grafo1 = EliminaAdjGrafo(Grafo1, 0, 1, &res);
	Grafo1 = EliminaAdjGrafo(Grafo1, 2, 3, &res);
	MostrarGrafo(Grafo1->inicioGrafo);

	printf("------------------------------------------------------------------------------------\n");
	printf("Remove Vertice\n");
	Grafo1 = EliminaVerticeGrafo(Grafo1, 1, &res);
	Grafo1 = EliminaVerticeGrafo(Grafo1, 3, &res);
	MostrarGrafo(Grafo1->inicioGrafo);
	
	printf("------------------------------------------------------------------------------------\n");

#pragma endregion

#pragma region Grafo
	int numLinhas, numColunas;
	Grafo* meuGrafo = carregarMatrizParaGrafo("Matriz.csv", &numLinhas, &numColunas);
	if (meuGrafo == NULL) {
		printf("Erro ao carregar o grafo.\n");
	}

	GuardaGrafoBinario(meuGrafo, "guarda.bin");
	
	int resultado = CarregaGrafoBinario("guarda.bin");

	if (resultado == 0) {
		printf("Grafo carregado do ficheiro binário com sucesso.\n");
	}
	else {
		printf("Erro ao carregar o grafo.\n");
	}
	

	printf("\nRepresentação do Grafo:\n");
	MostrarGrafo(meuGrafo->inicioGrafo);



	int origem = 0;
	int destino = 4;
	int somaCaminhos;

	printf("Todos os caminhos possíveis com inicio em %d e final em %d são:\n\n", origem, destino);
	ProcuraProfundidade(meuGrafo, origem, destino, numLinhas, &somaCaminhos);
	printf("\n\nSoma dos valores dos vértices em todos os caminhos: %d\n\n", somaCaminhos);


	encontrarCaminhoMaiorSoma(meuGrafo, origem, destino, numLinhas);

	free(meuGrafo);
#pragma endregion

}