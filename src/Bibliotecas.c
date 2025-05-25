/**

    @file      Bibliotecas.c
    @brief     
    @details   
    @author    Jo�o Barbosa
    @date      22.05.2024
    @copyright Jo�o Barbosa, 2024. All right reserved.

**/
#include "Biblioteca.h"

#pragma region Vertices 
/**
 * @brief Cria um novo v�rtice com o identificador especificado.
 *
 * Esta fun��o aloca dinamicamente mem�ria para um novo v�rtice e inicializa seus campos.
 *
 * @param id O identificador do v�rtice a ser criado.
 * @return Um apontador para o v�rtice criado, ou NULL se a aloca��o de mem�ria falhar.
 */
Vertices* CriaVertice(int id) {
	Vertices* aux = (Vertices*)malloc(sizeof(Vertices));
	if (aux == NULL)
	{
		return NULL;
	}
	aux->id = id;

	aux->proxVertice = NULL;
	aux->proxAdj = NULL;
	return aux;
}


/**
 * @brief Verifica se um v�rtice com o identificador especificado existe na lista encadeada.
 *
 * Esta fun��o percorre uma lista encadeada de v�rtices para verificar se existe um v�rtice
 * com o identificador especificado.
 *
 * @param inicio Um apontador para o in�cio da lista encadeada de v�rtices.
 * @param id O identificador do v�rtice a ser verificado.
 * @return true se um v�rtice com o identificador especificado existir na lista, false caso contr�rio.
 */
bool ExisteVertice(Vertices* inicio, int id) {
	if (inicio == NULL) return false;
	Vertices* aux = inicio;
	while (aux) {
		if (aux->id == id) return true;
		aux = aux->proxVertice;
	}
	return false;
}


/**
 * @brief Insere um novo v�rtice em uma lista encadeada ordenada de v�rtices.
 *
 * Esta fun��o insere um novo v�rtice em uma lista encadeada ordenada de v�rtices,
 * mantendo a ordena��o crescente dos identificadores dos v�rtices.
 *
 * @param vertices Um apontador para o in�cio da lista encadeada de v�rtices.
 * @param novo Um apontador para o v�rtice a ser inserido.
 * @param res Um ponteiro para uma vari�vel booleana que indicar� se a inser��o foi bem-sucedida.
 * @return Um apontador para o in�cio da lista encadeada de v�rtices ap�s a inser��o.
 */
Vertices* InsereVertice(Vertices* vertices, Vertices* novo, bool* res) {
	*res = false;

	//Insere no grafo vazio
	if (vertices == NULL) {
		*res = 1;
		vertices = novo;
		return vertices;
	}

	//verificar se V j� existe na lista de vertices
	if (ExisteVertice(vertices, novo->id)) {
		return vertices;
	}
	else {
		//procura onde inserir
		Vertices* ant = NULL;
		Vertices* aux = vertices;
		while (aux != NULL && aux->id < novo->id)
		{
			ant = aux;
			aux = aux->proxVertice;
		}
		//Insere
		*res = true;
		if (ant == NULL) {
			novo->proxVertice = vertices;	//insere no inicio
			vertices = novo;
		}
		else {
			novo->proxVertice = aux;
			ant->proxVertice = novo;
		}
	}
	return vertices;
}


/**
 * @brief Encontra um v�rtice com o identificador especificado em uma lista encadeada.
 *
 * Esta fun��o percorre uma lista encadeada de v�rtices para encontrar um v�rtice
 * com o identificador especifico.
 *
 * @param inicio Um apontador para o in�cio da lista encadeada de v�rtices.
 * @param id O identificador do v�rtice a ser encontrado.
 * @return Um apontador para o v�rtice com o identificador especificado, ou NULL se n�o for encontrado.
 */
Vertices* OndeEstaVertice(Vertices* inicio, int id) {
	if (inicio == NULL) return NULL;
	Vertices* aux = inicio;
	while (aux) {
		if (aux->id == id) return aux;
		aux = aux->proxVertice;
	}
	return NULL;
}


/**
 * @brief Liberta a mem�ria alocada para a estrutura de adjac�ncias.
 *
 * Esta fun��o libera a mem�ria alocada para a estrutura de adjac�ncias.
 *
 * @param destroir Um apontador para a estrutura de adjac�ncias a ser liberada.
 */
void destroiAdjacencias(Adjacencias* destroir) {
	free(destroir);
}


/**
 * @brief Liberta a mem�ria alocada para todas as adjac�ncias em uma lista encadeada de adjac�ncias.
 *
 * Esta fun��o percorre uma lista encadeada de adjac�ncias e liberta a mem�ria alocada para cada n�.
 *
 * @param listaAdjacencias Um apontador para o in�cio da lista encadeada de adjac�ncias.
 * @param res Um ponteiro para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador NULL, indicando que todas as adjac�ncias foram eliminadas.
 */
Adjacencias* EliminaAllAdj(Adjacencias* listaAdjacencias, bool* res) {
	*res = false;
	if (listaAdjacencias == NULL) return NULL;

	// Percorre a lista de adjac�ncias e liberta a mem�ria
	Adjacencias* aux = listaAdjacencias;
	Adjacencias* prox;
	while (aux != NULL) {
		prox = aux->next;
		free(aux);
		aux = prox;
	}
	*res = true;
	return NULL; // Retorna NULL indicando que todas as adjac�ncias foram eliminadas
}


/**
 * @brief Remove uma adjac�ncia com o c�digo especifico de uma lista encadeada de adjac�ncias.
 *
 * Esta fun��o remove uma adjac�ncia com o c�digo especifico de uma lista encadeada de adjac�ncias,
 * se ela existir.
 *
 * @param listaAdjacencias Um apontador para o in�cio da lista encadeada de adjac�ncias.
 * @param codAdj O c�digo da adjac�ncia a ser removida.
 * @param res Um ponteiro para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador para o in�cio da lista encadeada de adjac�ncias ap�s a remo��o.
 *         Se a adjac�ncia com o c�digo especifico n�o for encontrada, retorna a lista original.
 */
Adjacencias* EliminaAdj(Adjacencias* listaAdjacencias, int codAdj, bool* res) {
	*res = false;
	if (listaAdjacencias == NULL) return NULL;

	Adjacencias* ant = NULL;
	Adjacencias* aux = listaAdjacencias;
	while (aux && aux->id != codAdj) {
		ant = aux;
		aux = aux->next;
	}
	if (aux == NULL) return listaAdjacencias; // Adjac�ncia n�o encontrada

	if (ant == NULL) {
		// A adjac�ncia a ser removida � a primeira da lista
		listaAdjacencias = aux->next;
	}
	else {
		// A adjac�ncia a ser removida n�o � a primeira da lista
		ant->next = aux->next;
	}
	free(aux);
	*res = true;
	return listaAdjacencias;
}


/**
 * @brief Remove um v�rtice com o c�digo especificado de uma lista encadeada de v�rtices.
 *
 * Esta fun��o remove um v�rtice com o c�digo especificado de uma lista encadeada de v�rtices,
 * se ele existir. Al�m disso, elimina todas as adjac�ncias associadas ao v�rtice removido.
 *
 * @param vertices Um apontador para o in�cio da lista encadeada de v�rtices.
 * @param codVertice O c�digo do v�rtice a ser removido.
 * @param res Um apontador para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador para o in�cio da lista encadeada de v�rtices ap�s a remo��o.
 *         Se o v�rtice com o c�digo especificado n�o for encontrado, retorna a lista original.
 */
Vertices* EliminaVertice(Vertices* vertices, int codVertice, bool* res) {
	*res = false;
	if (vertices == NULL) return NULL;

	Vertices* ant = NULL;
	Vertices* aux = vertices;
	while (aux && aux->id != codVertice) {
		ant = aux;
		aux = aux->proxVertice;
	}
	if (aux == NULL) return vertices; // Vertice n�o encontrado

	// Elimina todas as adjac�ncias do v�rtice a ser removido
	aux->proxAdj = EliminaAllAdj(aux->proxAdj, res);
	if (*res == false) return vertices;

	if (ant == NULL) {
		// O v�rtice a ser removido � o primeiro da lista
		vertices = aux->proxVertice;
	}
	else {
		ant->proxVertice = aux->proxVertice;
	}
	*res = true;
	return vertices;
}


/**
 * @brief Remove todas as adjac�ncias com o c�digo especificado em uma lista encadeada de v�rtices.
 *
 * Esta fun��o remove todas as adjac�ncias com o c�digo especifico em uma lista encadeada de v�rtices,
 * se elas existirem. Para cada v�rtice na lista, as adjac�ncias correspondentes s�o removidas.
 *
 * @param vertices Um apontador para o in�cio da lista encadeada de v�rtices.
 * @param codAdj O c�digo da adjac�ncia a ser removida.
 * @param res Um apontador para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador para o in�cio da lista encadeada de v�rtices ap�s a remo��o das adjac�ncias.
 */
Vertices* EliminaAdjacenciaVertices(Vertices* vertices, int codAdj, bool* res) {
	*res = false;
	if (vertices == NULL) return NULL;

	Vertices* aux = vertices;
	while (aux) {
		// Remove a adjac�ncia em cada v�rtice
		aux->proxAdj = EliminaAdj(aux->proxAdj, codAdj, res);
		if (*res == false) return vertices;
		aux = aux->proxVertice;
	}
	*res = true;
	return vertices;
}

#pragma endregion 

#pragma region arestas

/**
 * @brief Cria uma nova adjac�ncia com o identificador e peso especifico.
 *
 * Esta fun��o aloca dinamicamente mem�ria para uma nova adjac�ncia e inicializa os seus campos
 * com o identificador e peso especificados.
 *
 * @param id O identificador da adjac�ncia.
 * @param peso O peso da adjac�ncia.
 * @return Um apontador para a nova adjac�ncia criada, ou NULL se a aloca��o de mem�ria falhar.
 */
Adjacencias* NovaAdjacencia(int id, int peso) {
	Adjacencias* adjacente = (Adjacencias*)malloc(sizeof(Adjacencias));
	if (adjacente == NULL) {
		return NULL; // Falha na aloca��o de mem�ria
	}
	adjacente->id = id;
	adjacente->peso = peso;
	adjacente->next = NULL;
	return adjacente;
}

/**
 * @brief Insere uma nova adjac�ncia com o identificador e peso especificados em uma lista encadeada de adjac�ncias.
 *
 * Esta fun��o cria uma nova adjac�ncia com o identificador e peso especificados e a insere
 * em uma lista encadeada de adjac�ncias.
 *
 * @param listaAdja Um apontador para o in�cio da lista encadeada de adjac�ncias.
 * @param idDestino O identificador do v�rtice de destino da adjac�ncia.
 * @param peso O peso da adjac�ncia.
 * @return Um apontador para o in�cio da lista encadeada de adjac�ncias ap�s a inser��o.
 */
Adjacencias* InsereAdj(Adjacencias* listaAdja, int idDestino, int peso) {
	Adjacencias* newAdj;
	if ((newAdj = NovaAdjacencia(idDestino, peso)) == NULL) {
		return listaAdja; // Falha ao criar nova adjac�ncia
	}

	// Se a lista de adjac�ncias estava vazia
	if (listaAdja == NULL) {
		listaAdja = newAdj; // Insere a nova adjac�ncia no in�cio
	}
	else {
		// Insere no final da lista de adjac�ncias
		Adjacencias* aux = listaAdja;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = newAdj;
	}
	return listaAdja;
}

/**
 * @brief Liberta a mem�ria alocada para uma adjac�ncia.
 *
 * Esta fun��o liberta a mem�ria alocada para uma adjac�ncia.
 *
 * @param ptAdjacent Um apontador para a adjac�ncia a ser destru�da.
 */
void DestroiAdjacencia(Adjacencias* ptAdjacent) {
	free(ptAdjacent);
}


/**
 * @brief Remove todas as adjac�ncias de uma lista encadeada de adjac�ncias e liberta a mem�ria alocada.
 *
 * Esta fun��o percorre uma lista encadeada de adjac�ncias, liberta a mem�ria alocada para cada n�
 * e define a lista como vazia.
 *
 * @param listAdj Um apontador para o in�cio da lista encadeada de adjac�ncias.
 * @param res Um apontador para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador NULL, indicando que todas as adjac�ncias foram removidas e a lista est� vazia.
 */
Adjacencias* EliminaTodasAdjacencias(Adjacencias* listAdj, bool* res) {
	*res = false;
	if (listAdj == NULL) return NULL;

	// Percorre a lista de adjac�ncia e libera a mem�ria
	Adjacencias* aux = listAdj;
	while (aux) {
		Adjacencias* prox = aux->next;
		DestroiAdjacencia(aux);
		aux = prox;
	}
	listAdj = NULL;
	*res = true;
	return listAdj;
}

#pragma endregion

#pragma region Grafo

/**
 * @brief Cria um novo grafo.
 *
 * Esta fun��o aloca dinamicamente mem�ria para um novo grafo e inicializa seus campos.
 *
 * @return Um apontador para o novo grafo criado, ou NULL se a aloca��o de mem�ria falhar.
 */
Grafo* CriaGrafo() {
	Grafo* novoGrafo = (Grafo*)malloc(sizeof(Grafo));
	if (novoGrafo == NULL) {
		return NULL;
	}

	novoGrafo->inicioGrafo = NULL;

	return novoGrafo;
}

/**
 * @brief Verifica se um v�rtice com o identificador especifico existe no grafo.
 *
 * Esta fun��o verifica se um v�rtice com o identificador especifico existe no grafo.
 *
 * @param g Um apontador para o grafo.
 * @param idVertice O identificador do v�rtice a ser verificado.
 * @return true se um v�rtice com o identificador especificado existir no grafo, false caso contr�rio.
 */
bool ExisteVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return false;
	return (ExisteVertice(g->inicioGrafo, idVertice));
}


/**
 * @brief Insere um novo v�rtice no grafo.
 *
 * Esta fun��o insere um novo v�rtice no grafo, realizando algumas valida��es.
 *
 * @param g Um apontador para o grafo.
 * @param novo Um apontador para o v�rtice a ser inserido.
 * @param res Um ponteiro para uma vari�vel inteira que indica o resultado da opera��o:
 *            1 - inser��o bem-sucedida,
 *            0 - v�rtice inv�lido,
 *           -1 - grafo vazio,
 *           -2 - v�rtice j� existente no grafo.
 * @return Um apontador para o grafo ap�s a inser��o do v�rtice.
 */
Grafo* InsereVerticeGrafo(Grafo* g, Vertices* novo, int* res) {
	*res = 1;
	if (novo == NULL) { //vertice invalido
		*res = 0;
		return g;
	}
	if (g == NULL) { // grafo vazio
		*res = -1;
		return NULL;
	}
	//verificar se V j� existe no grafo...
	if (ExisteVerticeGrafo(g, novo->id)) { //vertice desconhecido
		*res = -2;
		return g;
	}

	g->inicioGrafo = InsereVertice(g->inicioGrafo, novo, res);

	return g;
}


/**
 * @brief Encontra um v�rtice com o identificador especificado no grafo.
 *
 * Esta fun��o verifica se um v�rtice com o identificador especificado existe no grafo e retorna um apontador para ele.
 *
 * @param g Um apontador para o grafo.
 * @param idVertice O identificador do v�rtice a ser encontrado.
 * @return Um apontador para o v�rtice com o identificador especificado, ou NULL se n�o for encontrado.
 */
Vertices* OndeEstaVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return NULL;
	return (OndeEstaVertice(g->inicioGrafo, idVertice));
}


/**
 * @brief Remove um v�rtice com o c�digo especificado do grafo, juntamente com todas as suas adjac�ncias.
 *
 * Esta fun��o remove um v�rtice com o c�digo especificado do grafo, juntamente com todas as suas adjac�ncias.
 *
 * @param g Um apontador para o grafo.
 * @param codVertice O c�digo do v�rtice a ser removido.
 * @param res Um ponteiro para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador para o grafo ap�s a remo��o do v�rtice e suas adjac�ncias.
 */
Grafo* EliminaVerticeGrafo(Grafo* g, int codVertice, bool* res) {
	*res = false;
	if (g == NULL) return NULL;

	g->inicioGrafo = EliminaVertice(g->inicioGrafo, codVertice, res);
	g->inicioGrafo = EliminaAdjacenciaVertices(g->inicioGrafo, codVertice, res);

	return g;
}


/**
 * @brief Remove uma adjac�ncia entre dois v�rtices do grafo.
 *
 * Esta fun��o remove uma adjac�ncia entre dois v�rtices do grafo, se eles existirem.
 *
 * @param g Um apontador para o grafo.
 * @param origem O identificador do v�rtice de origem da adjac�ncia.
 * @param destino O identificador do v�rtice de destino da adjac�ncia.
 * @param res Um ponteiro para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador para o grafo ap�s a remo��o da adjac�ncia entre os v�rtices.
 */
Grafo* EliminaAdjGrafo(Grafo* g, int origem, int destino, bool* res) {

	*res = false;

	//valida��es
	if (g == NULL) return NULL;
	//Verificar se vertices existem
	Vertices* origemV = OndeEstaVerticeGrafo(g, origem);
	if (origemV == NULL) return g;
	Vertices* destinoV = OndeEstaVerticeGrafo(g, destino);
	if (!destinoV) return g;

	origemV->proxAdj = EliminaAdj(origemV->proxAdj, destino, res);
	return g;
}



/**
 * @brief Insere uma nova adjac�ncia entre dois v�rtices no grafo.
 *
 * Esta fun��o insere uma nova adjac�ncia entre dois v�rtices no grafo, se eles existirem.
 *
 * @param g Um apontador para o grafo.
 * @param idOrigem O identificador do v�rtice de origem da adjac�ncia.
 * @param idDestino O identificador do v�rtice de destino da adjac�ncia.
 * @param peso O peso da adjac�ncia.
 * @param res Um ponteiro para uma vari�vel booleana que indica se a opera��o foi bem-sucedida.
 * @return Um apontador para o grafo ap�s a inser��o da adjac�ncia entre os v�rtices.
 */
Grafo* InsereAdjacenciasGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* res) {
	if (res == NULL) {
		return g;
	}
	*res = false;

	if (g == NULL) {
		return g;
	}

	// Verificar se os v�rtices de origem e destino existem no grafo
	Vertices* origemV = OndeEstaVerticeGrafo(g, idOrigem);
	Vertices* destinoV = OndeEstaVerticeGrafo(g, idDestino);
	if (origemV == NULL || destinoV == NULL) {
		return g;
	}

	// Inserir a nova adjac�ncia na lista de adjac�ncias do v�rtice de origem
	origemV->proxAdj = InsereAdj(origemV->proxAdj, idDestino, peso);
	if (origemV->proxAdj == NULL) {
		return g;
	}

	*res = true;
	return g;
}


/**
 * @brief Mostra na sa�da padr�o a representa��o do grafo.
 *
 * Esta fun��o mostra na sa�da padr�o a representa��o do grafo, exibindo os v�rtices
 * e suas adjac�ncias, juntamente com os pesos das adjac�ncias.
 *
 * @param grafo Um apontador para o primeiro v�rtice do grafo.
 */
void MostrarGrafo(Vertices* grafo) {
	Vertices* atual = grafo;
	while (atual != NULL) {
		printf("vertice:%d \n", atual->id);
		Adjacencias* AdjacenciaAtual = atual->proxAdj;
		while (AdjacenciaAtual != NULL)
		{
			printf("\tadjacente com:%d com peso de:%d \n", AdjacenciaAtual->id, AdjacenciaAtual->peso);
			AdjacenciaAtual = AdjacenciaAtual->next;
		}
		atual = atual->proxVertice;
		printf("\n");
	}
}



#pragma endregion


/**
 * @brief Carrega uma matriz de um ficheiro e a converte em um grafo.
 *
 * Esta fun��o l� uma matriz de um ficheiro delimitado por ponto e v�rgula,
 * cria um grafo a partir dos dados da matriz, onde cada c�lula n�o-nula
 * representa uma aresta com peso entre dois v�rtices.Se a c�lula for nula
 * a aresta n�o ser� implementada.
 *
 * @param fileName O nome do ficheiro que contem a matriz.
 * @param numLinhas Um apontador para um inteiro onde o n�mero de linhas da matriz ser� armazenado.
 * @param numColunas Um apontador para um inteiro onde o n�mero de colunas da matriz ser� armazenado.
 *
 * @return Um apontador para o grafo criado a partir da matriz, ou NULL em caso de erro.
 *
 */
Grafo* carregarMatrizParaGrafo(char fileName[], int* numLinhas, int* numColunas) {
	FILE* fp;
	char linha[MAXCHAR];
	char* token;

	fp = fopen(fileName, "r");
	if (fp == NULL) {
		return NULL;
	}

	*numLinhas = 0;
	*numColunas = 0;

	Grafo* grafo = CriaGrafo();
	if (grafo == NULL) {
		fclose(fp);
		return NULL;
	}
	// ciclo para ler cada linha do arquivo
	while (fgets(linha, MAXCHAR, fp) != NULL) {
		// Incrementa o n�mero de linhas
		(*numLinhas)++;
		token = strtok(linha, ";");
		int colunaAtual = 0;
		while (token != NULL) {
			int valor = atoi(token);
			if (valor != 0) {
				// Verifica se o v�rtice de origem existe, se n�o, cria
				if (!ExisteVerticeGrafo(grafo, *numLinhas - 1)) {
					Vertices* novoVertice = CriaVertice(*numLinhas - 1);
					if (novoVertice == NULL) {
						fclose(fp);
						return NULL;
					}
					int res;
					grafo = InsereVerticeGrafo(grafo, novoVertice, &res);
					if (res != 1) {
						fclose(fp);
						return NULL;
					}
				}
				// Verifica se o v�rtice de destino existe, se n�o, cria
				if (!ExisteVerticeGrafo(grafo, colunaAtual)) {
					Vertices* novoVertice = CriaVertice(colunaAtual);
					if (novoVertice == NULL) {
						fclose(fp);

						return NULL;
					}
					int res;
					grafo = InsereVerticeGrafo(grafo, novoVertice, &res);
					if (res != 1) {
						fclose(fp);
						return NULL;
					}
				}
				bool res;
				grafo = InsereAdjacenciasGrafo(grafo, *numLinhas - 1, colunaAtual, valor, &res);
				if (!res) {
					fclose(fp);
					return NULL;
				}
			}
			// Avan�a para a proxima coluna
			token = strtok(NULL, ";");
			colunaAtual++;
		}
		if (colunaAtual > *numColunas) {
			*numColunas = colunaAtual;
		}
	}

	fclose(fp);
	return grafo;
}


/**
 * @brief Guarda a estrutura de um grafo em um ficheiro bin�rio.
 *
 * Esta fun��o percorre todos os v�rtices e as suas adjac�ncias de um grafo e escreve as informa��es
 * em um ficheiro bin�rio para que possam ser recuperadas posteriormente.
 *
 * @param grafo Apontador para a estrutura do grafo que ser� guardado.
 * @param fileName Nome do ficheiro bin�rio onde o grafo ser� guardado.
 * @return true se o grafo foi salvo com sucesso, false caso contr�rio.
 *
 */
bool GuardaGrafoBinario(Grafo* grafo, char fileName[]) {
	if (grafo == NULL || fileName == NULL) {
		return false;
	}

	FILE* fp = fopen(fileName, "wb");
	if (fp == NULL) {
		return false;
	}

	Vertices* verticeAtual = grafo->inicioGrafo;
	while (verticeAtual != NULL) {
		// Escreve o v�rtice atual no ficheiro bin�rio
		if (fwrite(&verticeAtual->id, sizeof(int), 1, fp) != 1) {
			fclose(fp);
			return false;
		}

		// Escreve o n�mero de adjac�ncias do v�rtice atual
		int numAdjacencias = 0;
		Adjacencias* adjacenciaAtual = verticeAtual->proxAdj;
		while (adjacenciaAtual != NULL) {
			numAdjacencias++;
			adjacenciaAtual = adjacenciaAtual->next;
		}
		if (fwrite(&numAdjacencias, sizeof(int), 1, fp) != 1) {
			fclose(fp);
			return false;
		}

		// Escreve as adjac�ncias do v�rtice atual no ficheiro bin�rio
		adjacenciaAtual = verticeAtual->proxAdj;
		while (adjacenciaAtual != NULL) {
			int adjData[2] = { adjacenciaAtual->id, adjacenciaAtual->peso };
			if (fwrite(adjData, sizeof(int), 2, fp) != 2) {
				fclose(fp);
				return false;
			}
			adjacenciaAtual = adjacenciaAtual->next;
		}

		verticeAtual = verticeAtual->proxVertice;
	}

	fclose(fp);
	return true;
}



/**
 * @brief Carrega a representa��o do grafo de um ficheiro bin�rio.
 *
 * Esta fun��o l� a estrutura do grafo de um ficheiro bin�rio, recriando os v�rtices e as adjac�ncias,
 * e exibe essas informa��es.
 *
 * @param fileName O nome do ficheiro bin�rio de onde o grafo ser� carregado.
 * @return Retorna 0 se o grafo foi carregado com sucesso, caso contr�rio retorna -1.
 */
int CarregaGrafoBinario(char fileName[]) {
	FILE* fp = fopen(fileName, "rb");
	if (fp == NULL) {
		return -1;
	}

	while (1) {
		int idVertice;
		if (fread(&idVertice, sizeof(int), 1, fp) != 1) {
			if (feof(fp)) break; 
			fclose(fp);
			return -1;
		}

		int numAdjacencias;
		if (fread(&numAdjacencias, sizeof(int), 1, fp) != 1) {
			fclose(fp);
			return -1;
		}

		for (int i = 0; i < numAdjacencias; i++) {
			int adjData[2];
			if (fread(adjData, sizeof(int), 2, fp) != 2) {
				fclose(fp);
				return -1;
			}
		}
	}

	fclose(fp);
	return 0;
}

/**
 * @brief Realiza uma procura em profundidade recursiva (DFS) num grafo.
 *
 * Esta fun��o percorre recursivamente o grafo a partir de um v�rtice de origem,
 * procurando todos os caminhos at� um v�rtice de destino. Durante a procura,
 * os v�rtices visitados s�o marcados, e os caminhos encontrados s�o armazenados
 * e somados.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem O v�rtice de origem para a procura.
 * @param destino O v�rtice de destino para a procura.
 * @param visitado Array de booleanos que indica se um v�rtice foi visitado.
 * @param caminho Array para armazenar o caminho atual.
 * @param indice �ndice do pr�ximo elemento no caminho.
 * @param somaCaminhos Apontador para a vari�vel que acumula a soma dos caminhos.
 * @return Apontador para a estrutura do grafo.
 */
Grafo* ProcuraProfundidadeRec(Grafo* g, int origem, int destino, bool* visitado, int* caminho, int indice, int* somaCaminhos) {
	visitado[origem] = true;
	caminho[indice] = origem; // Adiciona o v�rtice atual ao caminho
	indice++;

	if (origem == destino) {
		// Se o v�rtice atual � o destino, imprime o caminho
		for (int i = 0; i < indice; i++) {
			printf("%d ", caminho[i]);
		}
		printf("\n");

		// Calcula a soma dos valores dos v�rtices no caminho
		int soma = 0;
		for (int i = 0; i < indice; i++) {
			soma += caminho[i];
		}
		*somaCaminhos += soma;
	}
	else {
		// Se o v�rtice atual n�o � o destino, procura as adjac�ncias
		Vertices* verticeAtual = OndeEstaVerticeGrafo(g, origem);
		Adjacencias* adj = verticeAtual->proxAdj;
		while (adj != NULL) {
			if (!visitado[adj->id]) {
				ProcuraProfundidadeRec(g, adj->id, destino, visitado, caminho, indice, somaCaminhos);
			}
			adj = adj->next;
		}
	}

	indice--;                 // Decrementa o �ndice do caminho para backtracking
	visitado[origem] = false; // Marca o v�rtice atual como n�o visitado para permitir outros caminhos

	return g;
}


/**
 * @brief Realiza uma procura em profundidade (DFS) em um grafo e calcula a soma dos caminhos.
 *
 * Esta fun��o inicia a procura em profundidade a partir de um v�rtice de origem,
 * procurando todos os caminhos poss�veis at� o v�rtice de destino. Durante a procura,
 * os v�rtices visitados s�o marcados, e os caminhos encontrados s�o somados.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem O v�rtice de origem para a procura.
 * @param destino O v�rtice de destino para a procura.
 * @param numVertices O n�mero de v�rtices no grafo.
 * @param soma Apontador para a vari�vel que ir� armazenar a soma dos valores dos v�rtices nos caminhos encontrados.
 * @return Apontador para a estrutura do grafo.
 */
Grafo* ProcuraProfundidade(Grafo* g, int origem, int destino, int numVertices, int* soma) {
	bool* visitado = (bool*)malloc(numVertices * sizeof(bool)); 
	int* caminho = (int*)malloc(numVertices * sizeof(int));     
	int somaCaminhos = 0;                                       

	for (int i = 0; i < numVertices; i++) {
		visitado[i] = false; // Inicializa todos os v�rtices como n�o visitados
	}

	ProcuraProfundidadeRec(g, origem, destino, visitado, caminho, 0, &somaCaminhos);

	*soma = somaCaminhos;
	return g;
}



/**
 * @brief Realiza uma procura em profundidade (DFS) em um grafo para encontrar o caminho com a maior soma de pesos entre dois v�rtices.
 *
 * Esta fun��o percorre recursivamente o grafo a partir de um v�rtice de origem, procurando o v�rtice de destino. Durante o percurso,
 * calcula a soma dos pesos das arestas no caminho e compara com a maior soma j� encontrada at� o momento.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem ID do v�rtice de origem.
 * @param destino ID do v�rtice de destino.
 * @param visitado Array de booleanos indicando se um v�rtice foi visitado durante o percurso.
 * @param caminho Array para armazenar o caminho atual.
 * @param indice �ndice atual no caminho.
 * @param somaCaminhos Apontador para a vari�vel que armazena a soma dos pesos dos caminhos encontrados (n�o utilizado nesta fun��o).
 * @param somaMaxima Apontador para a vari�vel que armazena a maior soma de pesos encontrada.
 * @param caminhoMaximo Array para armazenar o caminho correspondente � maior soma encontrada.
 * @param numVertices N�mero total de v�rtices no grafo.
 * @return Apontador para a estrutura do grafo.
 */
Grafo* DFSrec(Grafo* g, int origem, int destino, bool* visitado, int* caminho, int indice, int* somaCaminhos, int* somaMaxima, int* caminhoMaximo, int numVertices) {
	visitado[origem] = true;
	caminho[indice] = origem; // Armazena o ID do v�rtice atual no caminho
	indice++;

	if (origem == destino) {
		// Calcula a soma dos pesos das arestas no caminho
		int soma = 0;
		for (int i = 0; i < indice - 1; i++) {
			Vertices* verticeAtual = g->inicioGrafo;
			// Localiza o v�rtice atual na lista de v�rtices do grafo
			while (verticeAtual != NULL && verticeAtual->id != caminho[i]) {
				verticeAtual = verticeAtual->proxVertice;
			}
			// Verifica se o v�rtice atual foi encontrado
			if (verticeAtual == NULL) {
				return NULL;
			}
			Adjacencias* adj = verticeAtual->proxAdj;
			// Percorre as adjac�ncias do v�rtice atual
			while (adj != NULL) {
				if (adj->id == caminho[i + 1]) {
					soma += adj->peso;
					break;
				}
				adj = adj->next;
			}
		}

		// Verifica se a soma � maior que a soma m�xima encontrada at� agora
		if (soma > *somaMaxima) {
			*somaMaxima = soma;
			// Atualiza o caminho m�ximo correspondente
			for (int i = 0; i < indice; i++) {
				caminhoMaximo[i] = caminho[i];
			}
			// Define -1 nos elementos restantes do caminho m�ximo
			for (int i = indice; i < numVertices; i++) {
				caminhoMaximo[i] = -1;
			}
		}
	}
	else {
		// Se o v�rtice atual n�o � o destino, procura as adjac�ncias
		Vertices* verticeAtual = g->inicioGrafo;
		// Localiza o v�rtice atual na lista de v�rtices do grafo
		while (verticeAtual != NULL && verticeAtual->id != origem) {
			verticeAtual = verticeAtual->proxVertice;
		}
		// Verifica se o v�rtice atual foi encontrado
		if (verticeAtual == NULL) {
			return NULL;
		}
		Adjacencias* adj = verticeAtual->proxAdj;
		// Percorre as adjac�ncias do v�rtice atual
		while (adj != NULL) {
			if (!visitado[adj->id]) {
				DFSrec(g, adj->id, destino, visitado, caminho, indice, somaCaminhos, somaMaxima, caminhoMaximo, numVertices);
			}
			adj = adj->next;
		}
	}

	// Backtracking
	indice--;
	visitado[origem] = false;
	return g;
}



/**
 * @brief Encontra o caminho que proporciona a maior soma poss�vel dos inteiros no grafo, seguindo a regra de conex�o estabelecida.
 *
 * Esta fun��o realiza uma busca em profundidade (DFS) no grafo a partir de um v�rtice de origem, procurando o v�rtice de destino.
 * Durante o percurso, calcula a soma dos pesos das arestas no caminho e compara com a maior soma j� encontrada at� o momento.
 * Ao final, exibe a soma m�xima e o caminho correspondente.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem ID do v�rtice de origem.
 * @param destino ID do v�rtice de destino.
 * @param numVertices N�mero total de v�rtices no grafo.
 */
void encontrarCaminhoMaiorSoma(Grafo* g, int origem, int destino, int numVertices) {
	bool* visitado = (bool*)malloc(sizeof(bool) * numVertices);

	int* caminho = (int*)malloc(sizeof(int) * numVertices);

	// Inicializa todos os v�rtices como n�o visitados
	for (int i = 0; i < numVertices; i++) {
		visitado[i] = false;
	}

	int somaCaminhos = 0;
	int somaMaxima = 0;
	int* caminhoMaximo = (int*)malloc(sizeof(int) * numVertices);

	DFSrec(g, origem, destino, visitado, caminho, 0, &somaCaminhos, &somaMaxima, caminhoMaximo, numVertices);

	//Mostra soma m�xima e o caminho correspondente
	printf("Soma m�xima: %d\n", somaMaxima);
	printf("Caminho correspondente: ");
	for (int i = 0; i < numVertices; i++) {
		if (caminhoMaximo[i] != -1) {
			printf("%d ", caminhoMaximo[i]);
		}
	}
	printf("\n");
}


