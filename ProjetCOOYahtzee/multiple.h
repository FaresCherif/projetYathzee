#pragma once
#include <iostream>
//#include <algorithm>
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
				tab[des[i].getValeur()-1]++;
				somme += des[i].getValeur();
			}


			int n = sizeof(tab) / sizeof(tab[0]);
			std::sort(tab, tab + n);

			//std::cout << "carre de " << T << " rapporte ";
			if (tab[n-1] >= T) {
				//std::cout << somme << "points" << std::endl;
				if (T == 5) {
					return 50;
				}
				else {
					return somme;
				}
			}
			else {
				//std::cout << "0 points" << std::endl;
				return 0;
			}
		}
	};
}