/*
 ============================================================================
 Name        : josephusProblem.c
 Author      : Natasha Kaweski e Vin�cius Ferreira
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

	// =======================
	// Inser��o de soldados
	// =======================

	// Escolhe um n�mero
	srand(time(0));

	// Declara��o de vari�veis
	int i;
	SLista* listax = inicializa();

	// Prop�sito de testes
	char nomes[5][20] = { "Joao", "Arthur", "Davi", "Joaquim", "Eduardo" };

	// Insere os 5 soldados na lista
	// e imprime a lista com os soldados inseridos.
	for (i = 0; i < 5; i++)
		listax = insereSoldadoNoCirc(listax, nomes[i], (i+1));

	imprimeSoldadosCirc(listax);

	// Quantidade de soldados na lista
	int quantidade = verificaQteSoldados(listax);
	printf("\nQuantidade de Soldados: %d\n\n", quantidade);

	// =======================
	// Execu��o de Josephus
	// =======================
	listax = executaJosephus(listax, quantidade);

	// Imprime
	printf("\nSoldado a executar a tarefa:\n");
	imprimeSoldadosCirc(listax);

	return EXIT_SUCCESS;
}

/*
 * Fun��o que aloca na mem�ria um soldado apontando pra ele mesmo
 */
SLista* cria_soldado(char* nome, int numero) {

	// Aloca na mem�ria o espa�o de um soldaddo
	SLista* soldado = (SLista*)malloc(sizeof(SLista));

	// Atribui os par�metros como os dados armazenados do espa�o em mem�ria
	soldado->num = numero;
	strcpy(soldado->nome, nome);
	soldado->prox = soldado;

	return soldado;
}

/*
 * Fun��o que remove um soldado da lista
 */
SLista* remove_soldado(SLista* lista, SLista* soldado) {

	SLista* aux = lista;

	// Verifica se a lista s� tem um soldado
	if (soldado == aux && soldado->prox == aux) {
		lista = inicializa();

	// Verifica se o soldado � o primeiro da lista
	} else if (soldado == aux) {
		lista = soldado->prox;

		do {
			aux = aux->prox;
		} while (aux->prox->prox != lista);

		aux->prox = lista;

	// Qualquer outra posi��o da lista
	} else {
		do {
			if (aux->prox == soldado) {
				aux->prox = soldado->prox;
				break;
			}

			aux = aux->prox;

		} while (aux->prox != lista);
	}

	// Limpa esse espa�o de mem�ria
	free(soldado);

	// Retorna a nova lista
	return lista;
}

/*
 * Fun��o Josephus
 */
SLista* executaJosephus(SLista* lista, int quantidade) {

	int i, num_soldado, num_iteracoes;
	srand(time(NULL));

	// Verifica se h� apenas um soldado na lista
	if (quantidade == 1) {
		printf("\n [!] Soldado escolhido: %s\n\n", lista->nome);
		return lista;
	}

	num_iteracoes = rand() % 20;
	num_soldado = rand() % quantidade;

	SLista* aux = lista;

	printf("Posicao do soldado inicial: %d\n", num_soldado);

	// O soldado sorteado vai ser a X intera��o do n�mero sorteado
	for (i = 0; i < num_soldado; i++)
		aux = aux->prox;

	printf("Soldado inicial: %s\nNum. de intera��es na adedanha: %d\n", aux->nome, num_iteracoes);

	// Percorre a lista X vezes a partir do soldado sorteado e elimina um soldado da lista
	for (i = 0; i < num_iteracoes; i++)
		aux = aux->prox;

	printf("Soldado eliminado: %s\n\n", aux->nome);
	lista = remove_soldado(lista, aux);

	return executaJosephus(lista, quantidade - 1);
}

/*
 * Fun��o que insere um soldado na lista
 */
SLista* insereSoldadoNoCirc(SLista* lista, char* nome, int num) {

	// Aloca��o do soldado na mem�ria
	SLista* soldado = cria_soldado(nome, num);

	/* Se lista existir (se n�o estiver vazia),
	 * percorre at� encontrar o �ltimo elemento.
	 * Liga o 'prox' do �ltimo soldado no novo soldado,
	 * liga o 'prox' do novo soldado na lista.
	 */
	if (!verificaCircVazio(lista)) {
		SLista* aux = lista;

		while (aux->prox != lista)
			aux = aux->prox;

		aux->prox = soldado; // Liga o �ltimo elemento da lista no novo registro
		soldado->prox = lista; // Fecha a lista circular, ligando o novo registro na lista
	}

	return soldado;
}

/*
 * Fun��o que imprime na tela a lista com os soldados inseridos
 */
void imprimeSoldadosCirc(SLista* lista) {

	SLista* aux = lista;

	if ( !verificaCircVazio(lista) ) {
		do {
			printf("Soldado: [%d] %s [%p]->[%p]\n", aux->num, aux->nome, aux, aux->prox);
			aux = aux->prox;

		} while (aux != lista);
	}
}

/*
 * Fun��o que inicializa a lista
 */
SLista* inicializa() {
	return NULL;
}

/*
 * Fun��o que verifica se a lista est� vazia
 */
int verificaCircVazio(SLista* lista) {
	return !lista;
}

/*
 * Fun��o que verifica a quantidade de soldados na lista
 */
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
