/*
 * PilhaSeq.h
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#ifndef PILHASEQ_H_
#define PILHASEQ_H_

#define TAM_MAX 100

class PilhaSeq {

private:
	int dados[TAM_MAX];
	int topo;

public:
	PilhaSeq();
	virtual ~PilhaSeq();

	bool vazia();
	bool cheia();
	int tamanho();
	int top();
	bool push(int valor);
	int pop();

};

#endif /* PILHASEQ_H_ */
