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

typedef struct soldado SLista;

struct soldado {
	char nome[20];
	int num;
	SLista* prox;
};

// Auxiliares
SLista* cria_soldado(char *nome, int numero);

SLista* inicializa();
int verificaCircVazio(SLista* lista);
SLista* insereSoldadoNoCirc(SLista* lista, char *nome, int num);
void imprimeSoldadosCirc(SLista* lista);
int verificaQteSoldados(SLista* lista);

int main(void) {

	// Proposito de testes
	char nomes[5][20]  = { "Joao", "Arthur", "Davi", "Joaquim", "Eduardo" };

	int i;
	SLista *listax = inicializa();

	// Insere os 5 soldados na lista
	for (i = 0; i < 5; i++)  {
		listax = insereSoldadoNoCirc(listax, nomes[i], (i+1));
	}

	// Imprime
	imprimeSoldadosCirc(listax);

	// Quantidade de Soldados
	printf("\nQuantidade de Soldados: %d", verificaQteSoldados(listax));

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
