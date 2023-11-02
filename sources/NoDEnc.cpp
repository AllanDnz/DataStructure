/*
 * No.cpp
 *
 *  Created on: 20 de out. de 2022
 *      Author: tiagomaritan
 */

#include "NoDEnc.h"
#include <stdlib.h>

NoDEnc::NoDEnc() {
	setAnt(NULL);
	setProx(NULL);
}

NoDEnc::~NoDEnc() {
}

int NoDEnc::getConteudo() {
	return conteudo;
}

void NoDEnc::setConteudo(int conteudo) {
	this->conteudo = conteudo;
}

NoDEnc *NoDEnc::getProx() {
	return prox;
}

void NoDEnc::setProx(NoDEnc *prox) {
	this->prox = prox;
}

NoDEnc *NoDEnc::getAnt() {
	return ant;
}

void NoDEnc::setAnt(NoDEnc *ant) {
	this->ant = ant;
}


