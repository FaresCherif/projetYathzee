#pragma once
#include "figure.h"

namespace COO {
	class full : public figure {
	public:
		int valFigure(de* des) {
			
			int cptFull1 = 0;
			int cptFull2 = 0;

			int full1 = des[0].getValeur();
			int full2=full1;

			for (int i = 0; i < 5; i++) {
				if (des[i] == full1) {
					cptFull1++;
				}
				else if (des[i] == full2) {
					cptFull2++;
				}
				else if (full2==full1) {
					full2 = des[i].getValeur();
					cptFull2++;
				}
			}

			//std::cout << "full de " << T1 <<" et "<<T2 << " rapporte ";
			if ((cptFull1 == 3 && cptFull2 ==2) || (cptFull1 ==2 && cptFull2==3)) {
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