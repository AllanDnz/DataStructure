/*
 * No.h
 *
 *  Created on: 19 de out. de 2022
 *      Author: Administrador
 */

#ifndef NOSENC_H_
#define NOSENC_H_

class NoSEnc {

private:
	int conteudo;
    NoSEnc *prox;

public:
    NoSEnc();
    virtual ~NoSEnc();

	int getConteudo();
    NoSEnc *getProx();

	void setConteudo(int conteudo);
    void setProx(NoSEnc *prox);


};

#endif /* NOSENC_H_ */
