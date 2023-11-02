/*
 * No.cpp
 *
 *  Created on: 19 de out. de 2022
 *      Author: Administrador
 */

#include <stdlib.h>
#include "NoSEnc.h"

NoSEnc::NoSEnc() {
	setConteudo(0);
	setProx(NULL);
}

NoSEnc::~NoSEnc() {
}


int NoSEnc::getConteudo() {
	return conteudo;
}

void NoSEnc::setConteudo(int conteudo) {
 this->conteudo = conteudo;
}

NoSEnc *NoSEnc::getProx(){
	return prox;
}

void NoSEnc::setProx(NoSEnc *prox) {
	this->prox = prox;
}

