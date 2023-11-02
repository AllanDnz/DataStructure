/*
 * LDE.cpp
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#include "LDE.h"
#include <stdlib.h>

LDE::LDE() {
	inicio = NULL;
	fim = NULL;
	nElementos = 0;
}

LDE::~LDE() {
}

/** Verifica se a Lista está vazia */
bool LDE::vazia() {
	if (nElementos == 0)
		return true;
	else
		 return false;
}

/**Obtém o tamanho da Lista*/
int LDE::tamanho() {
	return nElementos;
}

/** Obtém o i-ésimo elemento de uma lista
	Retorna o valor encontrado. */
int LDE::elemento (int pos) {
    NoDEnc *aux = inicio;
	int cont = 1;

	if (vazia())
		return -1; // Consulta falhou

	if ((pos < 1) || (pos > tamanho()))
		return -1; // Posicao invalida

	// Percorre a lista do 1o elemento até pos
	while (cont < pos){
		// modifica "aux" para apontar para o proximo elemento da lista
		aux = aux->getProx();
		cont++;
	}

	return aux->getConteudo();
}

/**Retorna a posição de um elemento pesquisado.
    Retorna 0 caso não seja encontrado */
int LDE::posicao (int dado) {
	int cont = 1;
    NoDEnc *aux;

	/* Lista vazia */
	if (vazia())
		return -1;

	/* Percorre a lista do inicio ao fim até encontrar o elemento*/
	aux = inicio;
	while (aux != NULL) {
		/* Se encontrar o elemento, retorna sua posicao n;*/
		if (aux->getConteudo() == dado)
			return cont;

		/* modifica "aux" para apontar para o proximo elemento da lista */
		aux = aux->getProx();
		cont++;
	}

	return -1;
}

	/** Insere nó em lista vazia */
bool LDE::insereInicioLista(int valor) {

	// Aloca memoria para novo no
    NoDEnc *novoNo = new NoDEnc();

	// Insere novo elemento na cabeca da lista
	novoNo->setConteudo(valor);
	novoNo->setProx(inicio);

	novoNo->setAnt(NULL); // Nova instrucao
	if (vazia())
		fim = novoNo; // Nova instrucao
	else
		inicio->setAnt(novoNo); // Nova instrucao

	inicio = novoNo;
	nElementos++;
	return true;
}

/** Insere nó no meio da lista */
bool LDE::insereMeioLista(int pos, int dado){

	int cont = 1;

	// Aloca memoria para novo no
    NoDEnc *novoNo = new NoDEnc();
	novoNo->setConteudo(dado);

	// Localiza a pos. onde será inserido o novo nó
    NoDEnc *aux = inicio;
	while ((cont < pos-1) && (aux != NULL)){
		aux = aux->getProx();
		cont++;
	}

	if (aux == NULL)   // pos. inválida
		return false;

	// Insere novo elemento apos aux
	novoNo->setAnt(aux); // Nova instrucao
	novoNo->setProx(aux->getProx());

	aux->getProx()->setAnt(novoNo); // Nova instrucao

	aux->setProx(novoNo);

	nElementos++;
	return true;
}

/** Insere nó no fim da lista */
bool LDE::insereFimLista(int dado){
	// Aloca memoria para novo no
    NoDEnc *novoNo = new NoDEnc();
	novoNo->setConteudo(dado);
	novoNo->setProx(NULL);

	fim->setProx(novoNo);

	novoNo->setAnt(fim);  // Nova instrucao
	fim->setProx(novoNo); // Nova instrucao
	fim = novoNo; 		// Nova instrucao

	nElementos++;
	return true;
}

/**Insere um elemento em uma determinada posição
	Retorna true se conseguir inserir e false caso contrario */
bool LDE::insere(int pos, int dado) {

	if ((vazia()) && (pos != 1))
		return false; // lista vazia mas posicao inv

	// inserção no início da lista (ou lista vazia)
	if (pos == 1)
		return insereInicioLista(dado);
	/* inserção no fim da lista */
	else if (pos == nElementos+1)
		return insereFimLista(dado);
	/* inserção no meio da lista */
	else
		return insereMeioLista(pos, dado);
}

/** Remove elemento do início de uma lista unitária */
int LDE::removeInicioListaUnitaria(){
	int dado = inicio->getConteudo();

	delete inicio;

	inicio = NULL;
	fim = NULL;
	nElementos--;
	return dado;
}

/** Remove elemento do início da lista */
int LDE::removeInicioLista(){
    NoDEnc *p = inicio;

	// Dado recebe o dado removido
	int dado = p->getConteudo();

	// Retira o 1o elemento da lista (p)
	inicio = p->getProx();
	p->getProx()->setAnt(NULL);  // Nova instrucao

	nElementos--;

	// Libera a memoria da regiao apontada por p
	delete p;

	return dado;
}

/** Remove elemento no meio da lista */
int LDE::removeMeioLista(int pos){
    NoDEnc *p = inicio;
	int n = 1;

	// Localiza o nó que será removido
	while((n <= pos-1) && (p != NULL)){
		p = p->getProx();
		n++;
	}

	if (p == NULL)
		return -1; // pos. inválida

	int dado = p->getConteudo();
	p->getAnt()->setProx(p->getProx());
	p->getProx()->setAnt(p->getAnt());

	nElementos--;

	// Libera a memoria da regiao apontada por p
	delete p;

	return dado;
}

/** Remove elemento do início da lista */
int LDE::removeFimLista(){
    NoDEnc *p = fim;
	int dado = p->getConteudo();

	fim->getAnt()->setProx(NULL);
	fim = fim->getAnt();
	nElementos--;

	delete p;

	return dado;
}


/**Remove um elemento de uma determinada posição
	Retorna o valor a ser removido.
	-1 se a posição for inválida ou a lista estiver vazia*/
int LDE::remove(int pos) {
	// Lista vazia
	if (vazia())
		return -1;

	// Remoção do elemento da cabeça da lista
	if ((pos == 1) && (tamanho() == 1))
		return removeInicioListaUnitaria();
	else if (pos == 1)
		return removeInicioLista();
	// Remocao no fim da lista
	else if (pos == tamanho())
		return removeFimLista();
	// Remoção em outro lugar da lista
	else
		return removeMeioLista(pos);
}


