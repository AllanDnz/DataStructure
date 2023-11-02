/*
 * FilaSeq.cpp
 *
 *  Created on: 10 de nov. de 2022
 *      Author: Administrador
 */

#include "FilaSeq.h"

FilaSeq::FilaSeq() {
	inicio = 0;
	fim = -1;
	nElementos = 0;
}

FilaSeq::~FilaSeq() {
}



/** Verifica se a Fila está vazia */
bool FilaSeq::vazia() {
	return (nElementos == 0);
}

	/**Verifica se a Fila está cheia */
bool FilaSeq::cheia() {
	return (nElementos == TAM_MAX);
}

/** Obtém o tamanho da Fila */
int FilaSeq::tamanho() {
	return nElementos;
}

/** Consulta o elemento do início da fila.
 *  Retorna -1 se a fila estiver vazia. */
int FilaSeq::primeiro() {
	if (vazia())
		return -1; // Erro: Fila vazia

	return dados[inicio];
}

/**Insere um elemento no fim de uma fila
	Retorna false se a fila estiver cheia, true caso contrário. */
bool FilaSeq::insere(int valor) {
	if (cheia())
		return false;

	fim = (fim + 1) % TAM_MAX; // Circularidade
	dados[fim] = valor;
	nElementos++;
	return true;
}

/**Remove o elemento do início da fila e retorna o valor removido.
 * Retorna -1 se a fila estiver vazia.*/
int FilaSeq::remove() {
	if (vazia())
		return -1;

	// Guarda o valor a ser removido
	//int valor = primeiro();
	int valor = dados[inicio];

	// Atualiza o atributo inicio;
	inicio = (inicio + 1) % TAM_MAX; //Circularidade
	nElementos--;
	return valor;
}


