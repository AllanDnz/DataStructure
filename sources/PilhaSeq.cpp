/*
 * PilhaSeq.cpp
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#include "PilhaSeq.h"

PilhaSeq::PilhaSeq() {
	topo = -1;
}

PilhaSeq::~PilhaSeq() {
}

/** Verifica se a Pilha está vazia */
bool PilhaSeq::vazia(){
	if (topo == -1)
		return true;
	else
		return false;
}

/**Verifica se a Pilha está cheia */
bool PilhaSeq::cheia(){
	if (topo == (TAM_MAX -1))
		return true;
	else
		return false;
}

/**Obtém o tamanho da Pilha*/
int PilhaSeq::tamanho(){
	return topo+1;
}

/** Consulta o elemento do topo da Pilha.
	Retorna -1 se a pilha estiver vazia,
	caso contrário retorna o valor que está no topo da pilha. */
int PilhaSeq::top() {
	if (vazia())
		return -1; // pilha vazia

	return dados[topo];
 }

/** Insere um elemento no topo da pilha.
	Retorna false se a pilha estiver cheia.
	Caso contrário retorna true */
bool PilhaSeq::push(int valor) {
	 if (cheia())
		 return false;  // err: pilha cheia

	 topo++;
	 dados[topo] = valor;
	 return true;
}

/** Retira o elemento do topo da pilha.
 	 Retorna -1 se a pilha estiver vazia. */
int PilhaSeq::pop() {
	if (vazia())
		return -1; // Pilha vazia

	int valor = dados[topo];
 	topo--;
 	return valor;
 }
