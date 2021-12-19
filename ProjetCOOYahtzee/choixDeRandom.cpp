#include "choixDeRandom.h"
#include <random>

namespace COO {

	int choixDeRandom::choixDe(std::vector<visibiliteFigure*> vecFigure, de* des,int difficulte)//defini comme l'IA random choisi son de
	{
		int choix;
		bool choixValide = false;

		while (!choixValide) {
			int nbAleatoire;

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 12); // distribution in range [1, 6]
			nbAleatoire = dist6(rng);

			// les differentes difficultes ont ete separer car meme si cela entraine de la duplication de code cela le rend aussi plus lisible

			if (vecFigure[nbAleatoire]->getFigureVu() == false) {

				if (difficulte == 1) {
					choix = nbAleatoire;
					choixValide = true;
					std::cout << "num aleatoire : " << choix << std::endl;

				}
				else if (difficulte == 2) {
					if (nbAleatoire > 5) {
						if (vecFigure[0]->getFigureVu() == true &&
							vecFigure[1]->getFigureVu() == true &&
							vecFigure[2]->getFigureVu() == true &&
							vecFigure[3]->getFigureVu() == true &&
							vecFigure[4]->getFigureVu() == true &&
							vecFigure[5]->getFigureVu() == true) {

							choix = nbAleatoire;
							choixValide = true;
							std::cout << "num aleatoire : " << choix << std::endl;
						}
					}
					else {
						choix = nbAleatoire;
						choixValide = true;
						std::cout << "num aleatoire : " << choix << std::endl;
					}
				}
				else if (difficulte == 3 || difficulte == 4) {
					int i = 0;
					while (vecFigure[i]->getFigureVu() == true)
					{
						i++;
					}
					choix = i;
					choixValide = true;
					std::cout << "num aleatoire : " << choix << std::endl;
				}

			}
		}
		return choix;
	}
	choixDeRandom::choixDeRandom()
	{
		this->type = typeJoueur::iaRandom;
	}

	typeJoueur choixDeRandom::getType() const
	{
		return strategyDe::getType();
	}

}