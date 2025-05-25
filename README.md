# Projeto de Grafos

## Descrição do Projeto

Este projeto, desenvolvido no âmbito de um trabalho académico, tem como objetivo implementar uma solução para calcular o somatório máximo de inteiros numa matriz arbitrária, utilizando conceitos avançados de teoria dos grafos e programação em C. A solução modela o problema como um grafo orientado, onde cada elemento da matriz é representado por um vértice e as conexões entre elementos adjacentes são representadas por arestas com pesos correspondentes aos valores da matriz.

## Funcionalidades Principais

- **Definição de Estrutura de Dados**: Implementação de uma estrutura de grafo orientado (`GR`) com suporte para um número variável de vértices e arestas.
- **Modelagem do Problema**: Representação dos elementos da matriz como vértices e conexões como arestas, com regras de conexão configuráveis (e.g., apenas na mesma linha ou coluna).
- **Carregamento de Dados**: Leitura de uma matriz de inteiros a partir de um ficheiro de texto, com valores separados por ponto e vírgula.
- **Manipulação de Grafos**: Implementação de algoritmos de procura em profundidade (DFS) para identificar todos os caminhos possíveis e calcular a soma dos valores dos vértices.
- **Soma Máxima**: Determinação do caminho com a maior soma de pesos, retornando tanto a soma máxima quanto o caminho correspondente.
- **Preservação de Dados**: Funções para guardar o grafo em formato binário e carregá-lo posteriormente.

## Estrutura do Projeto

- **Código-Fonte**: Contém a implementação em C, incluindo:
  - Estruturas de dados para vértices, arestas e grafos.
  - Funções para manipulação do grafo (criação, inserção, remoção de vértices e arestas).
  - Funções para carregar e guardar grafos em ficheiros.
  - Algoritmos de procura em profundidade para encontrar caminhos e calcular somas.
- **Ficheiros de Teste**: Inclui exemplos de matrizes de inteiros em ficheiros de texto para testar a funcionalidade do programa.
- **Documentação**: O relatório detalhado (`Relatório EDA.docx`) descreve a análise, modelagem, implementação, testes e conclusões do projeto.

## Requisitos

- **Linguagem**: C
- **Compilador**: Qualquer compilador C compatível (e.g., GCC)
- **Sistema Operativo**: Independente de plataforma (testado em Windows)
- **Dependências**: Bibliotecas padrão da linguagem C (e.g., `stdio.h`, `stdlib.h`, `string.h`)

## Instruções de Uso

### 1. Compilação
Compile o código-fonte utilizando um compilador C. Exemplo:
```bash
gcc -o programa main.c
```

### 2. Preparação do Ficheiro de Entrada
Crie um ficheiro de texto (e.g., matriz.txt) com a matriz de inteiros no formato especificado (valores separados por ponto e vírgula). Exemplo:
7;53;183;439;863
497;383;563;79;973
287;63;343;169;583
627;343;773;959;943
767;473;103;699;303

### 3. Execução
Execute o programa, fornecendo o nome do ficheiro de entrada e, se necessário, os parâmetros para a origem e destino do caminho. Exemplo:

./programa matriz.txt 0 4

### 4. Saída
O programa exibirá:

-Todos os caminhos possíveis entre os vértices de origem e destino (se aplicável).
-A soma máxima dos pesos das arestas e o caminho correspondente.
-O grafo pode ser guardado em formato binário para uso posterior.

### 5. Preservação do Grafo
-Utilize a função **GuardaGrafoBinario** para salvar o grafo num ficheiro binário.
-Utilize a função **CarregaGrafoBinario** para carregar o grafo previamente salvo.

## Notas de Implementação
-Estrutura de Dados: O grafo é representado por uma lista de vértices, onde cada vértice contém um identificador único e uma lista de adjacências (arestas). Cada aresta possui um identificador de destino e um peso.
-Algoritmo de Procura: A procura em profundidade (DFS) foi escolhida para explorar todos os caminhos possíveis, com recursividade para simplificar a implementação.
-Preservação: A escolha pelo formato binário garante eficiência em espaço e velocidade de leitura/escrita.
-Testes: Foram realizados testes com matrizes de diferentes dimensões para validar a robustez da solução.


## Limitações e Observações
O projeto utiliza uma única biblioteca para todas as funções (vértices, arestas e grafos) devido a dependências recursivas entre elas.
Ficheiros adicionais (e.g., .obj, .exe, .lib) podem ser necessários para garantir a compatibilidade com a solução completa.

## Referências
Código produzido nas aulas.
Notes on Data Structures and Programming Techniques (James Aspnes, 2015).
Data Structures Using C (Reema Thareja, 2nd Edition).
Fundamentos sobre Grafos (Professor Morais da Silva).

