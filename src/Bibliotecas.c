/**

    @file      Bibliotecas.c
    @brief     
    @details   
    @author    João Barbosa
    @date      22.05.2024
    @copyright João Barbosa, 2024. All right reserved.

**/
#include "Biblioteca.h"

#pragma region Vertices 
/**
 * @brief Cria um novo vértice com o identificador especificado.
 *
 * Esta função aloca dinamicamente memória para um novo vértice e inicializa seus campos.
 *
 * @param id O identificador do vértice a ser criado.
 * @return Um apontador para o vértice criado, ou NULL se a alocação de memória falhar.
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
 * @brief Verifica se um vértice com o identificador especificado existe na lista encadeada.
 *
 * Esta função percorre uma lista encadeada de vértices para verificar se existe um vértice
 * com o identificador especificado.
 *
 * @param inicio Um apontador para o início da lista encadeada de vértices.
 * @param id O identificador do vértice a ser verificado.
 * @return true se um vértice com o identificador especificado existir na lista, false caso contrário.
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
 * @brief Insere um novo vértice em uma lista encadeada ordenada de vértices.
 *
 * Esta função insere um novo vértice em uma lista encadeada ordenada de vértices,
 * mantendo a ordenação crescente dos identificadores dos vértices.
 *
 * @param vertices Um apontador para o início da lista encadeada de vértices.
 * @param novo Um apontador para o vértice a ser inserido.
 * @param res Um ponteiro para uma variável booleana que indicará se a inserção foi bem-sucedida.
 * @return Um apontador para o início da lista encadeada de vértices após a inserção.
 */
Vertices* InsereVertice(Vertices* vertices, Vertices* novo, bool* res) {
	*res = false;

	//Insere no grafo vazio
	if (vertices == NULL) {
		*res = 1;
		vertices = novo;
		return vertices;
	}

	//verificar se V já existe na lista de vertices
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
 * @brief Encontra um vértice com o identificador especificado em uma lista encadeada.
 *
 * Esta função percorre uma lista encadeada de vértices para encontrar um vértice
 * com o identificador especifico.
 *
 * @param inicio Um apontador para o início da lista encadeada de vértices.
 * @param id O identificador do vértice a ser encontrado.
 * @return Um apontador para o vértice com o identificador especificado, ou NULL se não for encontrado.
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
 * @brief Liberta a memória alocada para a estrutura de adjacências.
 *
 * Esta função libera a memória alocada para a estrutura de adjacências.
 *
 * @param destroir Um apontador para a estrutura de adjacências a ser liberada.
 */
void destroiAdjacencias(Adjacencias* destroir) {
	free(destroir);
}


/**
 * @brief Liberta a memória alocada para todas as adjacências em uma lista encadeada de adjacências.
 *
 * Esta função percorre uma lista encadeada de adjacências e liberta a memória alocada para cada nó.
 *
 * @param listaAdjacencias Um apontador para o início da lista encadeada de adjacências.
 * @param res Um ponteiro para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador NULL, indicando que todas as adjacências foram eliminadas.
 */
Adjacencias* EliminaAllAdj(Adjacencias* listaAdjacencias, bool* res) {
	*res = false;
	if (listaAdjacencias == NULL) return NULL;

	// Percorre a lista de adjacências e liberta a memória
	Adjacencias* aux = listaAdjacencias;
	Adjacencias* prox;
	while (aux != NULL) {
		prox = aux->next;
		free(aux);
		aux = prox;
	}
	*res = true;
	return NULL; // Retorna NULL indicando que todas as adjacências foram eliminadas
}


/**
 * @brief Remove uma adjacência com o código especifico de uma lista encadeada de adjacências.
 *
 * Esta função remove uma adjacência com o código especifico de uma lista encadeada de adjacências,
 * se ela existir.
 *
 * @param listaAdjacencias Um apontador para o início da lista encadeada de adjacências.
 * @param codAdj O código da adjacência a ser removida.
 * @param res Um ponteiro para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador para o início da lista encadeada de adjacências após a remoção.
 *         Se a adjacência com o código especifico não for encontrada, retorna a lista original.
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
	if (aux == NULL) return listaAdjacencias; // Adjacência não encontrada

	if (ant == NULL) {
		// A adjacência a ser removida é a primeira da lista
		listaAdjacencias = aux->next;
	}
	else {
		// A adjacência a ser removida não é a primeira da lista
		ant->next = aux->next;
	}
	free(aux);
	*res = true;
	return listaAdjacencias;
}


/**
 * @brief Remove um vértice com o código especificado de uma lista encadeada de vértices.
 *
 * Esta função remove um vértice com o código especificado de uma lista encadeada de vértices,
 * se ele existir. Além disso, elimina todas as adjacências associadas ao vértice removido.
 *
 * @param vertices Um apontador para o início da lista encadeada de vértices.
 * @param codVertice O código do vértice a ser removido.
 * @param res Um apontador para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador para o início da lista encadeada de vértices após a remoção.
 *         Se o vértice com o código especificado não for encontrado, retorna a lista original.
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
	if (aux == NULL) return vertices; // Vertice não encontrado

	// Elimina todas as adjacências do vértice a ser removido
	aux->proxAdj = EliminaAllAdj(aux->proxAdj, res);
	if (*res == false) return vertices;

	if (ant == NULL) {
		// O vértice a ser removido é o primeiro da lista
		vertices = aux->proxVertice;
	}
	else {
		ant->proxVertice = aux->proxVertice;
	}
	*res = true;
	return vertices;
}


/**
 * @brief Remove todas as adjacências com o código especificado em uma lista encadeada de vértices.
 *
 * Esta função remove todas as adjacências com o código especifico em uma lista encadeada de vértices,
 * se elas existirem. Para cada vértice na lista, as adjacências correspondentes são removidas.
 *
 * @param vertices Um apontador para o início da lista encadeada de vértices.
 * @param codAdj O código da adjacência a ser removida.
 * @param res Um apontador para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador para o início da lista encadeada de vértices após a remoção das adjacências.
 */
Vertices* EliminaAdjacenciaVertices(Vertices* vertices, int codAdj, bool* res) {
	*res = false;
	if (vertices == NULL) return NULL;

	Vertices* aux = vertices;
	while (aux) {
		// Remove a adjacência em cada vértice
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
 * @brief Cria uma nova adjacência com o identificador e peso especifico.
 *
 * Esta função aloca dinamicamente memória para uma nova adjacência e inicializa os seus campos
 * com o identificador e peso especificados.
 *
 * @param id O identificador da adjacência.
 * @param peso O peso da adjacência.
 * @return Um apontador para a nova adjacência criada, ou NULL se a alocação de memória falhar.
 */
Adjacencias* NovaAdjacencia(int id, int peso) {
	Adjacencias* adjacente = (Adjacencias*)malloc(sizeof(Adjacencias));
	if (adjacente == NULL) {
		return NULL; // Falha na alocação de memória
	}
	adjacente->id = id;
	adjacente->peso = peso;
	adjacente->next = NULL;
	return adjacente;
}

/**
 * @brief Insere uma nova adjacência com o identificador e peso especificados em uma lista encadeada de adjacências.
 *
 * Esta função cria uma nova adjacência com o identificador e peso especificados e a insere
 * em uma lista encadeada de adjacências.
 *
 * @param listaAdja Um apontador para o início da lista encadeada de adjacências.
 * @param idDestino O identificador do vértice de destino da adjacência.
 * @param peso O peso da adjacência.
 * @return Um apontador para o início da lista encadeada de adjacências após a inserção.
 */
Adjacencias* InsereAdj(Adjacencias* listaAdja, int idDestino, int peso) {
	Adjacencias* newAdj;
	if ((newAdj = NovaAdjacencia(idDestino, peso)) == NULL) {
		return listaAdja; // Falha ao criar nova adjacência
	}

	// Se a lista de adjacências estava vazia
	if (listaAdja == NULL) {
		listaAdja = newAdj; // Insere a nova adjacência no início
	}
	else {
		// Insere no final da lista de adjacências
		Adjacencias* aux = listaAdja;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		aux->next = newAdj;
	}
	return listaAdja;
}

/**
 * @brief Liberta a memória alocada para uma adjacência.
 *
 * Esta função liberta a memória alocada para uma adjacência.
 *
 * @param ptAdjacent Um apontador para a adjacência a ser destruída.
 */
void DestroiAdjacencia(Adjacencias* ptAdjacent) {
	free(ptAdjacent);
}


/**
 * @brief Remove todas as adjacências de uma lista encadeada de adjacências e liberta a memória alocada.
 *
 * Esta função percorre uma lista encadeada de adjacências, liberta a memória alocada para cada nó
 * e define a lista como vazia.
 *
 * @param listAdj Um apontador para o início da lista encadeada de adjacências.
 * @param res Um apontador para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador NULL, indicando que todas as adjacências foram removidas e a lista está vazia.
 */
Adjacencias* EliminaTodasAdjacencias(Adjacencias* listAdj, bool* res) {
	*res = false;
	if (listAdj == NULL) return NULL;

	// Percorre a lista de adjacência e libera a memória
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
 * Esta função aloca dinamicamente memória para um novo grafo e inicializa seus campos.
 *
 * @return Um apontador para o novo grafo criado, ou NULL se a alocação de memória falhar.
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
 * @brief Verifica se um vértice com o identificador especifico existe no grafo.
 *
 * Esta função verifica se um vértice com o identificador especifico existe no grafo.
 *
 * @param g Um apontador para o grafo.
 * @param idVertice O identificador do vértice a ser verificado.
 * @return true se um vértice com o identificador especificado existir no grafo, false caso contrário.
 */
bool ExisteVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return false;
	return (ExisteVertice(g->inicioGrafo, idVertice));
}


/**
 * @brief Insere um novo vértice no grafo.
 *
 * Esta função insere um novo vértice no grafo, realizando algumas validações.
 *
 * @param g Um apontador para o grafo.
 * @param novo Um apontador para o vértice a ser inserido.
 * @param res Um ponteiro para uma variável inteira que indica o resultado da operação:
 *            1 - inserção bem-sucedida,
 *            0 - vértice inválido,
 *           -1 - grafo vazio,
 *           -2 - vértice já existente no grafo.
 * @return Um apontador para o grafo após a inserção do vértice.
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
	//verificar se V já existe no grafo...
	if (ExisteVerticeGrafo(g, novo->id)) { //vertice desconhecido
		*res = -2;
		return g;
	}

	g->inicioGrafo = InsereVertice(g->inicioGrafo, novo, res);

	return g;
}


/**
 * @brief Encontra um vértice com o identificador especificado no grafo.
 *
 * Esta função verifica se um vértice com o identificador especificado existe no grafo e retorna um apontador para ele.
 *
 * @param g Um apontador para o grafo.
 * @param idVertice O identificador do vértice a ser encontrado.
 * @return Um apontador para o vértice com o identificador especificado, ou NULL se não for encontrado.
 */
Vertices* OndeEstaVerticeGrafo(Grafo* g, int idVertice) {
	if (g == NULL) return NULL;
	return (OndeEstaVertice(g->inicioGrafo, idVertice));
}


/**
 * @brief Remove um vértice com o código especificado do grafo, juntamente com todas as suas adjacências.
 *
 * Esta função remove um vértice com o código especificado do grafo, juntamente com todas as suas adjacências.
 *
 * @param g Um apontador para o grafo.
 * @param codVertice O código do vértice a ser removido.
 * @param res Um ponteiro para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador para o grafo após a remoção do vértice e suas adjacências.
 */
Grafo* EliminaVerticeGrafo(Grafo* g, int codVertice, bool* res) {
	*res = false;
	if (g == NULL) return NULL;

	g->inicioGrafo = EliminaVertice(g->inicioGrafo, codVertice, res);
	g->inicioGrafo = EliminaAdjacenciaVertices(g->inicioGrafo, codVertice, res);

	return g;
}


/**
 * @brief Remove uma adjacência entre dois vértices do grafo.
 *
 * Esta função remove uma adjacência entre dois vértices do grafo, se eles existirem.
 *
 * @param g Um apontador para o grafo.
 * @param origem O identificador do vértice de origem da adjacência.
 * @param destino O identificador do vértice de destino da adjacência.
 * @param res Um ponteiro para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador para o grafo após a remoção da adjacência entre os vértices.
 */
Grafo* EliminaAdjGrafo(Grafo* g, int origem, int destino, bool* res) {

	*res = false;

	//validações
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
 * @brief Insere uma nova adjacência entre dois vértices no grafo.
 *
 * Esta função insere uma nova adjacência entre dois vértices no grafo, se eles existirem.
 *
 * @param g Um apontador para o grafo.
 * @param idOrigem O identificador do vértice de origem da adjacência.
 * @param idDestino O identificador do vértice de destino da adjacência.
 * @param peso O peso da adjacência.
 * @param res Um ponteiro para uma variável booleana que indica se a operação foi bem-sucedida.
 * @return Um apontador para o grafo após a inserção da adjacência entre os vértices.
 */
Grafo* InsereAdjacenciasGrafo(Grafo* g, int idOrigem, int idDestino, int peso, bool* res) {
	if (res == NULL) {
		return g;
	}
	*res = false;

	if (g == NULL) {
		return g;
	}

	// Verificar se os vértices de origem e destino existem no grafo
	Vertices* origemV = OndeEstaVerticeGrafo(g, idOrigem);
	Vertices* destinoV = OndeEstaVerticeGrafo(g, idDestino);
	if (origemV == NULL || destinoV == NULL) {
		return g;
	}

	// Inserir a nova adjacência na lista de adjacências do vértice de origem
	origemV->proxAdj = InsereAdj(origemV->proxAdj, idDestino, peso);
	if (origemV->proxAdj == NULL) {
		return g;
	}

	*res = true;
	return g;
}


/**
 * @brief Mostra na saída padrão a representação do grafo.
 *
 * Esta função mostra na saída padrão a representação do grafo, exibindo os vértices
 * e suas adjacências, juntamente com os pesos das adjacências.
 *
 * @param grafo Um apontador para o primeiro vértice do grafo.
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
 * Esta função lê uma matriz de um ficheiro delimitado por ponto e vírgula,
 * cria um grafo a partir dos dados da matriz, onde cada célula não-nula
 * representa uma aresta com peso entre dois vértices.Se a célula for nula
 * a aresta não será implementada.
 *
 * @param fileName O nome do ficheiro que contem a matriz.
 * @param numLinhas Um apontador para um inteiro onde o número de linhas da matriz será armazenado.
 * @param numColunas Um apontador para um inteiro onde o número de colunas da matriz será armazenado.
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
		// Incrementa o número de linhas
		(*numLinhas)++;
		token = strtok(linha, ";");
		int colunaAtual = 0;
		while (token != NULL) {
			int valor = atoi(token);
			if (valor != 0) {
				// Verifica se o vértice de origem existe, se não, cria
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
				// Verifica se o vértice de destino existe, se não, cria
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
			// Avança para a proxima coluna
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
 * @brief Guarda a estrutura de um grafo em um ficheiro binário.
 *
 * Esta função percorre todos os vértices e as suas adjacências de um grafo e escreve as informações
 * em um ficheiro binário para que possam ser recuperadas posteriormente.
 *
 * @param grafo Apontador para a estrutura do grafo que será guardado.
 * @param fileName Nome do ficheiro binário onde o grafo será guardado.
 * @return true se o grafo foi salvo com sucesso, false caso contrário.
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
		// Escreve o vértice atual no ficheiro binário
		if (fwrite(&verticeAtual->id, sizeof(int), 1, fp) != 1) {
			fclose(fp);
			return false;
		}

		// Escreve o número de adjacências do vértice atual
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

		// Escreve as adjacências do vértice atual no ficheiro binário
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
 * @brief Carrega a representação do grafo de um ficheiro binário.
 *
 * Esta função lê a estrutura do grafo de um ficheiro binário, recriando os vértices e as adjacências,
 * e exibe essas informações.
 *
 * @param fileName O nome do ficheiro binário de onde o grafo será carregado.
 * @return Retorna 0 se o grafo foi carregado com sucesso, caso contrário retorna -1.
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
 * Esta função percorre recursivamente o grafo a partir de um vértice de origem,
 * procurando todos os caminhos até um vértice de destino. Durante a procura,
 * os vértices visitados são marcados, e os caminhos encontrados são armazenados
 * e somados.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem O vértice de origem para a procura.
 * @param destino O vértice de destino para a procura.
 * @param visitado Array de booleanos que indica se um vértice foi visitado.
 * @param caminho Array para armazenar o caminho atual.
 * @param indice Índice do próximo elemento no caminho.
 * @param somaCaminhos Apontador para a variável que acumula a soma dos caminhos.
 * @return Apontador para a estrutura do grafo.
 */
Grafo* ProcuraProfundidadeRec(Grafo* g, int origem, int destino, bool* visitado, int* caminho, int indice, int* somaCaminhos) {
	visitado[origem] = true;
	caminho[indice] = origem; // Adiciona o vértice atual ao caminho
	indice++;

	if (origem == destino) {
		// Se o vértice atual é o destino, imprime o caminho
		for (int i = 0; i < indice; i++) {
			printf("%d ", caminho[i]);
		}
		printf("\n");

		// Calcula a soma dos valores dos vértices no caminho
		int soma = 0;
		for (int i = 0; i < indice; i++) {
			soma += caminho[i];
		}
		*somaCaminhos += soma;
	}
	else {
		// Se o vértice atual não é o destino, procura as adjacências
		Vertices* verticeAtual = OndeEstaVerticeGrafo(g, origem);
		Adjacencias* adj = verticeAtual->proxAdj;
		while (adj != NULL) {
			if (!visitado[adj->id]) {
				ProcuraProfundidadeRec(g, adj->id, destino, visitado, caminho, indice, somaCaminhos);
			}
			adj = adj->next;
		}
	}

	indice--;                 // Decrementa o índice do caminho para backtracking
	visitado[origem] = false; // Marca o vértice atual como não visitado para permitir outros caminhos

	return g;
}


/**
 * @brief Realiza uma procura em profundidade (DFS) em um grafo e calcula a soma dos caminhos.
 *
 * Esta função inicia a procura em profundidade a partir de um vértice de origem,
 * procurando todos os caminhos possíveis até o vértice de destino. Durante a procura,
 * os vértices visitados são marcados, e os caminhos encontrados são somados.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem O vértice de origem para a procura.
 * @param destino O vértice de destino para a procura.
 * @param numVertices O número de vértices no grafo.
 * @param soma Apontador para a variável que irá armazenar a soma dos valores dos vértices nos caminhos encontrados.
 * @return Apontador para a estrutura do grafo.
 */
Grafo* ProcuraProfundidade(Grafo* g, int origem, int destino, int numVertices, int* soma) {
	bool* visitado = (bool*)malloc(numVertices * sizeof(bool)); 
	int* caminho = (int*)malloc(numVertices * sizeof(int));     
	int somaCaminhos = 0;                                       

	for (int i = 0; i < numVertices; i++) {
		visitado[i] = false; // Inicializa todos os vértices como não visitados
	}

	ProcuraProfundidadeRec(g, origem, destino, visitado, caminho, 0, &somaCaminhos);

	*soma = somaCaminhos;
	return g;
}



/**
 * @brief Realiza uma procura em profundidade (DFS) em um grafo para encontrar o caminho com a maior soma de pesos entre dois vértices.
 *
 * Esta função percorre recursivamente o grafo a partir de um vértice de origem, procurando o vértice de destino. Durante o percurso,
 * calcula a soma dos pesos das arestas no caminho e compara com a maior soma já encontrada até o momento.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @param visitado Array de booleanos indicando se um vértice foi visitado durante o percurso.
 * @param caminho Array para armazenar o caminho atual.
 * @param indice Índice atual no caminho.
 * @param somaCaminhos Apontador para a variável que armazena a soma dos pesos dos caminhos encontrados (não utilizado nesta função).
 * @param somaMaxima Apontador para a variável que armazena a maior soma de pesos encontrada.
 * @param caminhoMaximo Array para armazenar o caminho correspondente à maior soma encontrada.
 * @param numVertices Número total de vértices no grafo.
 * @return Apontador para a estrutura do grafo.
 */
Grafo* DFSrec(Grafo* g, int origem, int destino, bool* visitado, int* caminho, int indice, int* somaCaminhos, int* somaMaxima, int* caminhoMaximo, int numVertices) {
	visitado[origem] = true;
	caminho[indice] = origem; // Armazena o ID do vértice atual no caminho
	indice++;

	if (origem == destino) {
		// Calcula a soma dos pesos das arestas no caminho
		int soma = 0;
		for (int i = 0; i < indice - 1; i++) {
			Vertices* verticeAtual = g->inicioGrafo;
			// Localiza o vértice atual na lista de vértices do grafo
			while (verticeAtual != NULL && verticeAtual->id != caminho[i]) {
				verticeAtual = verticeAtual->proxVertice;
			}
			// Verifica se o vértice atual foi encontrado
			if (verticeAtual == NULL) {
				return NULL;
			}
			Adjacencias* adj = verticeAtual->proxAdj;
			// Percorre as adjacências do vértice atual
			while (adj != NULL) {
				if (adj->id == caminho[i + 1]) {
					soma += adj->peso;
					break;
				}
				adj = adj->next;
			}
		}

		// Verifica se a soma é maior que a soma máxima encontrada até agora
		if (soma > *somaMaxima) {
			*somaMaxima = soma;
			// Atualiza o caminho máximo correspondente
			for (int i = 0; i < indice; i++) {
				caminhoMaximo[i] = caminho[i];
			}
			// Define -1 nos elementos restantes do caminho máximo
			for (int i = indice; i < numVertices; i++) {
				caminhoMaximo[i] = -1;
			}
		}
	}
	else {
		// Se o vértice atual não é o destino, procura as adjacências
		Vertices* verticeAtual = g->inicioGrafo;
		// Localiza o vértice atual na lista de vértices do grafo
		while (verticeAtual != NULL && verticeAtual->id != origem) {
			verticeAtual = verticeAtual->proxVertice;
		}
		// Verifica se o vértice atual foi encontrado
		if (verticeAtual == NULL) {
			return NULL;
		}
		Adjacencias* adj = verticeAtual->proxAdj;
		// Percorre as adjacências do vértice atual
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
 * @brief Encontra o caminho que proporciona a maior soma possível dos inteiros no grafo, seguindo a regra de conexão estabelecida.
 *
 * Esta função realiza uma busca em profundidade (DFS) no grafo a partir de um vértice de origem, procurando o vértice de destino.
 * Durante o percurso, calcula a soma dos pesos das arestas no caminho e compara com a maior soma já encontrada até o momento.
 * Ao final, exibe a soma máxima e o caminho correspondente.
 *
 * @param g Apontador para a estrutura do grafo.
 * @param origem ID do vértice de origem.
 * @param destino ID do vértice de destino.
 * @param numVertices Número total de vértices no grafo.
 */
void encontrarCaminhoMaiorSoma(Grafo* g, int origem, int destino, int numVertices) {
	bool* visitado = (bool*)malloc(sizeof(bool) * numVertices);

	int* caminho = (int*)malloc(sizeof(int) * numVertices);

	// Inicializa todos os vértices como não visitados
	for (int i = 0; i < numVertices; i++) {
		visitado[i] = false;
	}

	int somaCaminhos = 0;
	int somaMaxima = 0;
	int* caminhoMaximo = (int*)malloc(sizeof(int) * numVertices);

	DFSrec(g, origem, destino, visitado, caminho, 0, &somaCaminhos, &somaMaxima, caminhoMaximo, numVertices);

	//Mostra soma máxima e o caminho correspondente
	printf("Soma máxima: %d\n", somaMaxima);
	printf("Caminho correspondente: ");
	for (int i = 0; i < numVertices; i++) {
		if (caminhoMaximo[i] != -1) {
			printf("%d ", caminhoMaximo[i]);
		}
	}
	printf("\n");
}


