#include "chance.h"
#include <iostream>

namespace COO {
	int chance::valFigure(de* des){
		int somme = 0;
		for (int i = 0; i < 5; i++) {
			somme += des[i].getValeur();

		}

		//std::cout << "La chance rapporte "<< somme << " points" << std::endl;
		return somme;
	}

	int chance::getValeur()
	{
		return 9;
	}
}