/*
 * No.h
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#ifndef NODENC_H_
#define NODENC_H_

class NoDEnc {

private:
	int conteudo;
    NoDEnc *ant;
    NoDEnc *prox;

public:
    NoDEnc();
    virtual ~NoDEnc();

	int getConteudo();
    NoDEnc *getProx();
    NoDEnc *getAnt();

	void setConteudo(int conteudo);
    void setProx(NoDEnc *prox);
    void setAnt(NoDEnc *ant);

};

#endif /* NODENC_H_ */
