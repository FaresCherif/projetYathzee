//Fares Cherif

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
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 12); // genere un nombre aleatoire entre 0 et 12
			nbAleatoire = dist6(rng);

			// les differentes difficultes ont ete separer car meme si cela entraine de la duplication de code cela le rend aussi plus lisible

			if (vecFigure[nbAleatoire]->getFigureVu() == false) { //si la figure du nombre choisis n'a pas encore ete vu 

				if (difficulte == 1) {
					choix = nbAleatoire; // on accepte le numero aleatoire fourni
					choixValide = true;
					std::cout << "num aleatoire : " << choix << std::endl;

				}
				else if (difficulte == 2) {
					if (nbAleatoire > 5) { //si on choisis une figure de la partie inferieur
						if (vecFigure[0]->getFigureVu() == true &&
							vecFigure[1]->getFigureVu() == true &&
							vecFigure[2]->getFigureVu() == true &&
							vecFigure[3]->getFigureVu() == true &&
							vecFigure[4]->getFigureVu() == true &&
							vecFigure[5]->getFigureVu() == true) { //si la partie superieur a ete vu

							choix = nbAleatoire;// on accepte le numero aleatoire fourni
							choixValide = true;
							std::cout << "num aleatoire : " << choix << std::endl;
						}
					}
					else {
						choix = nbAleatoire;// on accepte le numero aleatoire fourni
						choixValide = true;
						std::cout << "num aleatoire : " << choix << std::endl;
					}
				}
				else if (difficulte == 3 || difficulte == 4) {
					int i = 0;
					while (vecFigure[i]->getFigureVu() == true)//cherche la premiere figure non vue
					{
						i++;
					}
					choix = i; // on accepte ce numero comme numero de figure
					choixValide = true; 
					std::cout << "num aleatoire : " << choix << std::endl;
				}

			}
		}
		return choix;
	}
	choixDeRandom::choixDeRandom()//le constructeur set le type de joueur a random
	{
		this->type = typeJoueur::iaRandom;
	}

	typeJoueur choixDeRandom::getType() const //retroune le type
	{
		return strategyDe::getType();
	}

}