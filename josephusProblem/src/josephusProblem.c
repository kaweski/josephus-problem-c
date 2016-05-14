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
	char nomeSoldado[10];
	int numero;
	SLista* proximo;
};

SLista* inicializando();

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
	for ( i = 0; i < 5; i++ ) {
		printf("%s", soldados[i]);
	}

	// Insere esses soldados no c�rculo
	circuloSoldados = insereSoldadoNoCirc(soldados, circuloSoldados);





	return EXIT_SUCCESS;
}

/*
 * Fun��o: Inicializa a lista circular.
 */
SLista* inicializando() {
	return NULL;
}

/*
 * Fun��o: Insere soldados na lista
 * Parametros: array com o nomes dos soltados, a lista a ser inserido os nomes
 */

insereSoldadoNoCirc(int num, SLista* lista) {
	return lista;
}

/*
 * Return
 * Param
 */
//verificaCircVazio();

/*
 * Return
 * Param
 */
//imprimeSoldadosCirc();

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
