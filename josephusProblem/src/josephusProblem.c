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

typedef struct soldado SLista;
struct soldado {
	char nomeSold[10];
	int numSold;
	SLista* proxSold;
};

SLista* inicializando();
int verificaCircVazio(SLista* lista);
SLista* insereSoldadoNoCirc(SLista* lista, char nome, int num);
void imprimeSoldadosCirc(SLista* lista);

int main(void) {

	/*
	 * Incializa-se a lista.
	 */
	SLista* circuloSoldados;
	circuloSoldados = inicializando();

	/*
	 * Cria uma matriz com o n�mero de soldados a serem inseridos na lista
	 */
	char soldados[5][10]  = { "Jo�o", "Arthur", "Davi", "Joaquim", "Eduardo" };

	int i;
	printf("Lista inicial de soldados:\n");
	for ( i = 0; i < 5; i++ )
		printf("%s, ", soldados[i]);

	// Insere esses soldados no c�rculo
	circuloSoldados = insereSoldadoNoCirc(circuloSoldados, soldados[1][10], 1);
	imprimeSoldadosCirc(circuloSoldados);

	return EXIT_SUCCESS;
}

/*
 * Fun��o: Inicializa a lista circular.
 */
SLista* inicializando() {
	return NULL;
}

/*
 * Verifica se a lista est� vazia
 */
int verificaCircVazio(SLista* lista) {
	return !lista;
}

/*
 * Fun��o: Insere soldados na lista
 * Parametros: array com o nomes dos soldados, a lista a ser inserido os nomes
 */

SLista* insereSoldadoNoCirc(SLista* lista, char nome, int num) {
	SLista* aux;
	aux = (SLista*) malloc(sizeof(SLista)); // Cria o registro na mem�ria
	aux->nomeSold[10] = nome; // Insere o nome do soldado
	aux->numSold = num; // Insere o n�mero do soldado

	// Agora pra tornar a lista circular e encadeada, segue-se a l�gica abaixo
	if ( verificaCircVazio(lista) ) {
		aux->proxSold = aux; // Se a lista estiver vazia, o primeiro registro deve apontar pra ele mesmo.
	}
	return aux; // Retorna o topo da lista
}

/*
 * Return
 * Param
 */
void imprimeSoldadosCirc(SLista* lista) {
	SLista* aux = lista;

	// Se a lista estiver vazia, nem entra na condi��o
	if(aux) {
		printf("\n\nSoldados no c�rculo:\n");
		do {
			printf( "%c, ", aux->nomeSold[10] );
			aux = aux->proxSold;
		} while ( aux != lista ); // Finaliza o loop
	}
}

/*
 * Return
 * Param
 */
//verificaQteSoldados();

/*
 * Return:
 * Param
 */
//executaJosephus();
