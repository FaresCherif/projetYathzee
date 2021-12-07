#pragma once
#include "figure.h"

namespace COO {
	template<int T>

	class carree : public figure {
	public:
		int valFigure(de* des) {
			int cpt = 0;
			int somme = 0;
			for (int i = 0; i < 5; i++) {
				if (des[i].getValeur() == T) {
					cpt++;
				}
				somme += des[i].getValeur();
			}

			//std::cout << "carre de " << T << " rapporte ";
			if (cpt >= 4) {
				//std::cout << somme << "points" << std::endl;
				return somme;
			}
			else {
				//std::cout << "0 points" << std::endl;
				return 0;
			}
		}
	};
}