#pragma once
#include "figure.h"

namespace COO {
	template<int T1,int T2,int T3,int T4,int T5>

	class grandeSuite : public figure {
	public:
		int valFigure(de* des) {
			bool nb1 = false;
			bool nb2 = false;
			bool nb3 = false;
			bool nb4 = false;
			bool nb5 = false;

			for (int i = 0; i < 5; i++) {
				if (des[i].getValeur() == T1) {
					nb1 = true;
				}
				else if (des[i].getValeur() == T2) {
					nb2 = true;
				}
				else if (des[i].getValeur() == T3) {
					nb3 = true;
				}
				else if (des[i].getValeur() == T4) {
					nb4 = true;
				}
				else if (des[i].getValeur() == T5) {
					nb5 = true;
				}
			}

			if (nb1 && nb2 && nb3 && nb4 && nb5) {
				//std::cout << "La grandeSuite " << T1 << " " << T2 << " " << T3 << " " << T4 << " "<<T5<< " rapporte 40 points" << std::endl;
				return 40;
			}
			else {
				//std::cout << "La grandeSuite " << T1 << " " << T2 << " " << T3 << " " << T4 << " " << T5 << " rapporte 0 points" << std::endl;
				return 0;
			}

		}

	};
}