#pragma once
#include "figure.h"

namespace COO {
	template <int T>

	class yahtzee : public figure {
	public:
		int valFigure(de* des) {
			bool yahtz = true;

			for (int i = 0; i < 5; i++) {
				if (des[i].getValeur() != T) {
					yahtz=false;
				}
			}

			if (yahtz) {
				//std::cout << "yahtzee de " << T <<" rapporte 50 points"<< std::endl;
				return 50;
			}
			else {
				//std::cout << "yahtzee de " << T <<" rapporte 0 points"<< std::endl;
				return 0;
			}
		}

	};
}