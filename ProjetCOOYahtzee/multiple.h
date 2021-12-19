//Fares Cherif

#pragma once
#include <iostream>
#include "figure.h"
#include <algorithm>


namespace COO {
	template<int T>

	class multiple : public figure {
	public:
		int valFigure(de* des) {

			int tab[6] = { 0,0,0,0,0,0 };
			int somme = 0;

			for (int i = 0; i < 5; i++) {
				tab[des[i].getValeur()-1]++;// compte le nombre de chaque face de des
				somme += des[i].getValeur(); //compte la somme totale des des
			}


			int n = sizeof(tab) / sizeof(tab[0]);
			std::sort(tab, tab + n); //trie le tableau par ordre croissant

			if (tab[n-1] >= T) { //on regarde a combien vaut la derniere case du tableau car ce sera ceele qui compte le plus de face identiques
				if (T == 5) { 
					return 50;
				}
				else {
					return somme;
				}
			}
			else { //si il n'y a pas assez de face identiques
				return 0;
			}
		}
	};
}