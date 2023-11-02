/*
 * LDE.h
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#ifndef LDE_H_
#define LDE_H_

#include "NoDEnc.h"

class LDE {

private:
    NoDEnc *inicio;
    NoDEnc *fim;
	int nElementos;

	bool insereInicioLista(int valor);
	bool insereMeioLista(int pos, int dado);
	bool insereFimLista(int dado);

	int removeInicioListaUnitaria();
	int removeInicioLista();
	int removeMeioLista(int pos);
	int removeFimLista();

public:
	LDE();
	virtual ~LDE();

	bool vazia();
	bool cheia();
	int tamanho();
	int elemento(int pos);
	int posicao (int valor);
	int posicao (int valor, int desloc);
	bool insere (int pos, int valor);
	int remove(int pos);



};

#endif /* LDE_H_ */
