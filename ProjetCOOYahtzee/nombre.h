//Fares Cherif

#pragma once
#include "figure.h"
#include <iostream>

namespace COO {
	template <int T>

	class nombre : public figure {
	public:
		int valFigure(de* des) {
			int cpt = 0;
			for (int i = 0; i < 5; i++) {//pour chaque de
				if (des[i] == T) { //compte le nombre de fois que la face de cette valeur est visible
					cpt++;
				}
			}

			return T*cpt;//retourne le nombre de fois qu'il y a une face  fois ca valeur
		}

	};
}