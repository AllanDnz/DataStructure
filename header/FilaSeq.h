/*
 * FilaSeq.h
 *
 *  Created on: 10 de nov. de 2022
 *      Author: Administrador
 */

#ifndef FILASEQ_H_
#define FILASEQ_H_

#define TAM_MAX 100
class FilaSeq {

private:
	int dados[TAM_MAX];
	int inicio;
	int fim;
	int nElementos;

public:
	FilaSeq();
	virtual ~FilaSeq();

	bool vazia();
	bool cheia();
	int tamanho();
	int primeiro();
	bool insere(int valor);
	int remove();
};

#endif /* FILASEQ_H_ */
