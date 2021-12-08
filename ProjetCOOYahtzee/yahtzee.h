#pragma once
#include "figure.h"

namespace COO {

	class yahtzee : public figure {
	public:
		int valFigure(de* des) {
			bool yahtz = true;
			int faceYahtzee = des[0].getValeur();

			for (int i = 0; i < 5; i++) {
				if (des[i].getValeur() != faceYahtzee) {
					return 0;
				}
			}

			return 50;

		}

	};
}