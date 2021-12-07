#pragma once
#include "figure.h"

namespace COO {
	template<int T1,int T2,int T3,int T4>

	class petiteSuite : public figure {
	public :
		int valFigure(de* des) {
			bool nb1=false;
			bool nb2=false;
			bool nb3=false;
			bool nb4=false;

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
			}

			if (nb1 && nb2 && nb3 && nb4) {
				//std::cout << "La petiteSuite " << T1 << " " << T2 << " " << T3 << " " << T4 <<" rapporte 30 points"<< std::endl;
				return 30;
			}
			else {
				//std::cout << "La petiteSuite " << T1 << " " << T2 << " " << T3 << " " << T4 << " rapporte 0 points" << std::endl;
				return 0;
			}
		}

	};
}