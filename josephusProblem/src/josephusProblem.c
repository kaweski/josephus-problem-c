/*
 ============================================================================
 Name        : josephusProblem.c
 Author      : Natasha Kaweski e Vinícius Ferreira
 Version     :
 Copyright   : Your copyright notice
 Description : O Problema de Josephus (Tenenbaum, 1989)
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <time.h>

typedef struct soldado SLista;

struct soldado {
	char nome[20];
	int num;
	SLista* prox;
};

// Auxiliares
SLista* cria_soldado(char *nome, int numero);
SLista* remove_soldado(SLista* lista, SLista* soldado);

SLista* inicializa();
int verificaCircVazio(SLista* lista);
SLista* insereSoldadoNoCirc(SLista* lista, char *nome, int num);
void imprimeSoldadosCirc(SLista* lista);
int verificaQteSoldados(SLista* lista);
SLista* executaJosephus(SLista *lista, int quantidade);

int main(void) {

	srand(time(0));

	// Proposito de testes
	char nomes[5][20]  = { "Joao", "Arthur", "Davi", "Joaquim", "Eduardo" };

	int i;
	SLista *listax = inicializa();

	// Insere os 5 soldados na lista
	for (i = 0; i < 5; i++)  {
		listax = insereSoldadoNoCirc(listax, nomes[i], (i+1));
	}

	int quantidade = verificaQteSoldados(listax);

	// Imprime
	imprimeSoldadosCirc(listax);

	// Quantidade de Soldados
	printf("\nQuantidade de Soldados: %d\n\n", quantidade);

	listax = executaJosephus(listax, quantidade);

	// Imprime
	imprimeSoldadosCirc(listax);

	return EXIT_SUCCESS;
}

// Aloca na memória um soldado apontando pra ele mesmo
SLista* cria_soldado(char *nome, int numero) {


	SLista *soldado = (SLista *)malloc(sizeof(SLista));
	soldado->num = numero;
	strcpy(soldado->nome, nome);
	soldado->prox = soldado;

	return soldado;
}

SLista* remove_soldado(SLista *lista, SLista *soldado) {

	SLista* aux = lista;

	if (soldado == aux && soldado->prox == aux) {
		lista = inicializa();

	} else if (soldado == aux) {
		lista = soldado->prox;

		do {
			aux = aux->prox;
		} while (aux->prox != lista);

		aux->prox = lista;

	} else {

		do {

			if (aux->prox == soldado) {
				aux->prox = soldado->prox;
				break;
			}

			aux = aux->prox;

		} while (aux->prox != lista);

	}

	free(soldado);
	return lista;
}

SLista* executaJosephus(SLista *lista, int quantidade) {

	int i, num_soldado, num_iteracoes;
	srand(time(NULL));

	if (quantidade == 1)
	{
		printf("\n [!] Soldado escolhido: %s\n\n", lista->nome);
		return lista;
	}

	num_iteracoes = rand() % 20;
	num_soldado = rand() % quantidade;

	SLista *aux = lista;

	printf("Posicao do soldado inicial: %d\n", num_soldado);

	//O soldado sorteado vai ser a X iteração do número sorteado
	for (i = 0; i < num_soldado; i++)
		aux = aux->prox;

	printf("Soldado inicial: %s\nNum. de iteracoes na adedanha: %d\n", aux->nome, num_iteracoes);

	//Percorre a lista X vezes a partir do soldado sorteado e elimina um da lista
	for (i = 0; i < num_iteracoes; i++)
		aux = aux->prox;

	printf("Soldado eliminado: %s\n\n", aux->nome);
	lista = remove_soldado(lista, aux);

	return executaJosephus(lista, quantidade - 1);
}

SLista* insereSoldadoNoCirc(SLista* lista, char *nome, int num) {

	// Alocação do soldado na memória
	SLista *soldado = cria_soldado(nome, num);

	/* Se lista existir (se não estiver vazia),
	 * percorre até encontrar o último elemento
	 * liga o 'prox' do novo soldado na lista,
	 * liga o 'prox' do último soldado no novo soldado.
	 */
	if (lista) {
		SLista* aux = lista;

		while (aux->prox != lista)
			aux = aux->prox;

		aux->prox = soldado; // Liga o último elemento da lista no novo registro
		soldado->prox = lista; // Fecha a lista circular, ligando o último registro na lista
	}

	return soldado;
}

void imprimeSoldadosCirc(SLista* lista) {

	SLista* aux = lista;

	if ( !verificaCircVazio(lista) ) {
		do {
			printf("Soldado: [%d] %s [%p]->[%p]\n", aux->num, aux->nome, aux, aux->prox);
			aux = aux->prox;

		} while (aux != lista);
	}
}

SLista* inicializa() {
	return NULL;
}

int verificaCircVazio(SLista* lista) {
	return !lista;
}

int verificaQteSoldados(SLista* lista) {
	int qtd = 0;
	SLista* aux = lista;

	if ( !verificaCircVazio(lista) ) {
		qtd++;
		while (aux->prox != lista) {
			qtd++;
			aux = aux->prox;
		}
	}

	return qtd;
}
