#include "chance.h"
#include <iostream>

namespace COO {
	int chance::valFigure(de* des){ //calcul ce qua va rappporter la chance
		int somme = 0;
		for (int i = 0; i < 5; i++) { //pour chaqu'un des des
			somme += des[i].getValeur();//ajoute la valeur du de
		}
		//std::cout << "La chance rapporte "<< somme << " points" << std::endl;
		return somme; //retrourne le total obtenu
	}


}