#include "choixDeRandom.h"
#include <random>

namespace COO {

	int choixDeRandom::choixDe(std::vector<visibiliteFigure*> vecFigure, de* des)
	{
		int choix;
		bool choixValide = false;

		while (!choixValide) {
			int nbAleatoire;

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 12); // distribution in range [1, 6]
			nbAleatoire = dist6(rng);

			if (vecFigure[nbAleatoire]->getFigureVu() == false) {
				choix = nbAleatoire;
				choixValide = true;
				std::cout << "num aleatoire : " << choix << std::endl;
			}
		}
		return choix;
	}
	choixDeRandom::choixDeRandom()
	{
		this->type = typeJoueur::iaRandom;
	}

}