#pragma once
#include "figure.h"
#include <iostream>

namespace COO {
	template <int T>

	class nombre : public figure {
	public:
		int valFigure(de* des) {
			int cpt = 0;
			for (int i = 0; i < 5; i++) {
				if (des[i].getValeur() == T) {
					cpt++;
				}
			}

			//std::cout << "Les " << T << " rapportent "<<T*cpt<<" points" << std::endl;
			return T*cpt;
		}

	};
}