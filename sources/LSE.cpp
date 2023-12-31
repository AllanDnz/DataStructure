/*
 * LSE.cpp
 *
 *  Created on: 19 de out. de 2022
 *      Author: Administrador
 */

#include "LSE.h"
#include <stdlib.h>

LSE::LSE() {
	cabeca = NULL;
	nElementos = 0;
}

LSE::~LSE() {
}


/** Verifica se a Lista está vazia */
bool LSE::vazia() {
	return (nElementos == 0);
}


/**Obtém o tamanho da Lista*/
int LSE::tamanho() {
	//return nElementos;

    NoSEnc *aux = cabeca;
	int cont = 0;
	while(aux != NULL){
		aux = aux->getProx();
		cont++;
	}
	return cont;
}

/** Obtém o i-ésimo elemento de uma lista
	  Retorna o valor encontrado. */
int LSE::elemento (int pos) {
	if (vazia())
		return -1; // Consulta falhou


	if ((pos < 1) || (pos > tamanho()))
		return -1; // Posicao invalida

    NoSEnc *aux = cabeca;

	// Percorre a lista do 1o elemento até pos
	for (int i =1; i < pos; i++){
		// modifica "aux" para apontar para o proximo elemento da lista
	    aux = aux->getProx();
	}

	return aux->getConteudo();
}

	/**Retorna a posição de um elemento pesquisado.
	    Retorna -1 caso não seja encontrado */
int LSE::posicao (int dado) {
	/* Lista vazia */
	if (vazia())
		return -1;

	/* Percorre a lista do inicio ao fim até encontrar o elemento*/
    NoSEnc *aux = cabeca;
	int cont = 1;
	while (aux != NULL) {
		// Se encontrar o elemento, retorna sua posicao n;
		if (aux->getConteudo() == dado){
			return cont;
		}
		// modifica "aux" para apontar para o proximo elemento da lista
		aux = aux->getProx();
	    cont++;
	}

	return -1;
}

	/** Insere nó em lista vazia */
bool LSE::insereInicioLista(int valor) {
	// Aloca memoria para novo no
    NoSEnc *novoNo = new NoSEnc();

	// Insere novo elemento na cabeca da lista
	novoNo->setConteudo(valor);

	novoNo->setProx(cabeca);
	cabeca = novoNo;
	nElementos++;
	return true;
}

/** Insere nó no meio da lista */
bool LSE::insereMeioLista(int pos, int valor){

	// Aloca memoria para novo no
    NoSEnc *novoNo = new NoSEnc();
	novoNo->setConteudo(valor);

	// Localiza a pos. ANTERIOR onde será inserido o novo nó
    NoSEnc *aux = cabeca;
	for (int i =1; i < pos-1; i++){
		// modifica "aux" para apontar para o proximo elemento da lista
		aux = aux->getProx();
	}

	// Insere novo elemento apos aux
	novoNo->setProx(aux->getProx());
	aux->setProx(novoNo);

	nElementos++;
	return true;
}


/**Insere um elemento em uma determinada posição
	    Retorna true se conseguir inserir e
	    false caso contrario */
bool LSE::insere(int pos, int valor) {
	if ((vazia()) && (pos != 1))
		return false; /* lista vazia mas posicao inv*/

	if ((pos <= 0) || pos > (nElementos+1))
		return false; // posicao invalida

	/* inserção no início da lista (ou lista vazia)*/
	if (pos == 1)
		return insereInicioLista(valor);
	else
		return insereMeioLista(pos, valor);
}

/** Remove elemento do início da lista */
int LSE::removeInicioLista(){

    NoSEnc *p = cabeca;

	// Dado recebe o dado removido
	int valorRemovido = p->getConteudo();

	// Retira o 1o elemento da lista (p)
	cabeca = p->getProx();
	nElementos--;

	// Remove o objeto apontado por p
	delete p;

	return valorRemovido;
}

	/** Remove elemento no meio da lista */
int LSE::removeNaLista(int pos){
	// Localiza os nó a ser removido (atual) e o seu
	// antecessor (antecessor)
    NoSEnc *antecessor = cabeca;
	for(int i = 1; i < pos-1; i++) {
		antecessor = antecessor->getProx();
	}

    NoSEnc *atual = antecessor->getProx();

	// Guarda o valor a ser removido
	int valorRemovido = atual->getConteudo();

	// Faz o campo prox de antecessor apontar pro prox de atual
	//No aux = atual.getProx();
	//antecessor.setProx(aux);
	antecessor->setProx(atual->getProx());

	// Decrementa o numero de elementos
	nElementos--;

	// Libera a area de memoria do no atual
	delete atual;

	return valorRemovido;
}

/**Remove um elemento de uma determinada posição
 	 Retorna o valor a ser removido.
	-1 se a posição for inválida ou a lista estiver vazia*/
int LSE::remove(int pos) {
	if (vazia())
		return -1; // Lista vazia

	if ((pos <= 0) || (pos > nElementos))
		return -1; // Posicao invalida

	if (pos == 1)
		return removeInicioLista();
	else
		return removeNaLista(pos);
}
