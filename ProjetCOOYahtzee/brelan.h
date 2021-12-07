#pragma once
#include <iostream>
#include "figure.h"

namespace COO {
	template <int T>

	class brelan : public figure {
	public :
		int valFigure(de* des) {
			int cpt = 0;
			int somme = 0;
			for (int i = 0; i < 5; i++) {
				if (des[i].getValeur() == T) {
					cpt++;
				}
				somme += des[i].getValeur();
			}

			//std::cout << "brelan de " << T<<" rapporte ";
			if (cpt >= 3) {
				//std::cout << somme << " points"<<std::endl;
				return somme;
			}
			else {
				//std::cout << "0 points" << std::endl;
				return 0;
			}
		}
	};
}