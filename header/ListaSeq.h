/*
 * ListaSeq.h
 *
 *  Created on: 19 de out. de 2022
 *      Author: Administrador
 */

#ifndef LISTASEQ_H_
#define LISTASEQ_H_

#define TAM_MAX 100

class ListaSeq {

private:
	int dados[TAM_MAX];
	int nElementos;

public:
	ListaSeq();
	virtual ~ListaSeq();

    bool vazia();
    bool cheia();
    int tamanho();
    int elemento(int pos);
    int posicao (int valor);
    int posicao (int valor, int desloc);
    bool insere (int pos, int valor);
    int remove(int pos);


};

#endif /* LISTASEQ_H_ */
