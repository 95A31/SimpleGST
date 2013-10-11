/*
 * GeneralizedSuffixTrees.cpp
 *
 *  Created on: 11/ott/2013
 *      Author: user
 */

#include "GeneralizedSuffixTrees.h"

GeneralizedSuffixTrees::GeneralizedSuffixTrees(string ss[], int numOfStrings) {
	//Root
	nodes.push_back(new Node());

	for(int i = 0; i < numOfStrings; i++){
		addString(ss[i]);
	}
}

GeneralizedSuffixTrees::~GeneralizedSuffixTrees() {
	// TODO Auto-generated destructor stub
}

void GeneralizedSuffixTrees::addString(string s){
	short lengthOfs= s.length();
	s.append(1,'$');

	for(int i  = 0; i < lengthOfs; i++){
		for(int j = 1; j < i + 1; j++ ){
			CaseInfo = findCase
		}
	}
	 UKKONEN(S)
	   /* Precondizione: S stringa di lunghezza length n. */
	   "Aggiungi ad S la sentinella ottenendo la stringa S $ di lunghezza n+1."
	   "Costruisci I_0."
	   for i ← 0 to n do
	     /* Estensione da Ii ad Ii+1. */
	     for j ← 1 to i + 1 do
	       "Cerca la ﬁne del cammino corrispondente al suffisso S[j, i]
	        della sottostringa S[1, i] di cui I_i è l'albero dei suffissi
	        implicito e, se necessario, estendi tale cammino aggiungendo
	        il carattere S[i+1] in modo tale che il suffisso S[j, i+1] di
	        S[1, i+1] sia rappresentato nell'albero."
}

