#pragma once
#include "figure.h"

namespace COO {
	template<int T1,int T2>
	class full : public figure {
	public:
		int valFigure(de* des) {
			
			int cptBrelan = 0;
			int cptPaire = 0;
			int somme = 0;
			for (int i = 0; i < 5; i++) {
				if (des[i].getValeur() == T1) {
					cptBrelan++;
				}
				else if (des[i].getValeur() == T2) {
					cptPaire++;
				}
			}

			//std::cout << "full de " << T1 <<" et "<<T2 << " rapporte ";
			if (cptBrelan == 3 && cptPaire ==2) {
				//std::cout << "25 points" << std::endl;
				return 25;
			}
			else {
				//std::cout << "0 points" << std::endl;
				return 0;
			}
			
		}

	};
}