#include "partie.h"
#include <vector>
#include <iostream>

namespace COO {
	partie::partie(std::vector<joueur*> vecJoueur)
	{
		this->joueurs = vecJoueur;
	}

	void partie::jouer() {
		for (int i = 0; i < this->nbFigure-1; i++) {
			int nbJoueur = 1;
			for (joueur *f : joueurs) {
				std::cout << "Le joueur "<<nbJoueur<<" a " << f->getScore() << " points" << std::endl;
				f->jouer();
				std::cout << "Le joueur " << nbJoueur << " fini a " << f->getScore() << " points" << std::endl<<std::endl<<std::endl;

				nbJoueur++;
			}
		}

		int nbJoueur = 1;

		for (joueur* f : joueurs) {
			std::cout << "Le joueur " << nbJoueur << " a " << f->getScore()<<" points "<<std::endl;
			nbJoueur++;
		}
	}
}