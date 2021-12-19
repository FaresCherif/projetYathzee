//Fares Cherif

#pragma once
#include "figure.h"

namespace COO {
	class full : public figure {
	public:
		int valFigure(de* des) { //retourne la valeur du full
			
			int cptFull1 = 0; 
			int cptFull2 = 0;

			int full1 = des[0].getValeur(); //initialise full1 a la face du premier de
			int full2=full1;

			for (int i = 0; i < 5; i++) { //pour chacun des de
				if (des[i] == full1) {
					cptFull1++; //compte le nombre de face egale a full 1
				}
				else if (des[i] == full2) {
					cptFull2++; //compte le nombre de full2
				}
				else if (full2==full1) { //si full2 n'a pas encore ete defini et que la fasse n'est pas egale a full1
					full2 = des[i].getValeur(); //full2 prend la valeur de cette face
					cptFull2++; //le nombre de full2 est de 1
				}
			}

			if ((cptFull1 == 3 && cptFull2 ==2) || (cptFull1 ==2 && cptFull2==3)) { //si il y a 3 fois une face et 2 fois une autre
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