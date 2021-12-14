#include "partie.h"
#include <vector>
#include <iostream>
#include "nombre.h"
#include "multiple.h"
#include "suite.h"
#include "full.h"
#include "chance.h"

namespace COO {//just to backup
	partie::partie(std::vector<joueur*> vecJoueur)
	{
		this->joueurs = vecJoueur;

		std::vector<visibiliteFigure*> figureJoueur;

		figureJoueur.push_back(new visibiliteFigure(new nombre<1>, "un"));
		figureJoueur.push_back(new visibiliteFigure(new nombre<2>, "deux"));
		figureJoueur.push_back(new visibiliteFigure(new nombre<3>, "trois"));
		figureJoueur.push_back(new visibiliteFigure(new nombre<4>, "quatre"));
		figureJoueur.push_back(new visibiliteFigure(new nombre<5>, "cinq"));
		figureJoueur.push_back(new visibiliteFigure(new nombre<6>, "six"));
		figureJoueur.push_back(new visibiliteFigure(new multiple<3>, "brelan"));
		figureJoueur.push_back(new visibiliteFigure(new full, "full"));
		figureJoueur.push_back(new visibiliteFigure(new multiple<4>, "carree"));
		figureJoueur.push_back(new visibiliteFigure(new suite<4>, "petiteSuite"));
		figureJoueur.push_back(new visibiliteFigure(new suite<5>, "grandeSuite"));
		figureJoueur.push_back(new visibiliteFigure(new multiple<5>, "yahtzee"));
		figureJoueur.push_back(new visibiliteFigure(new chance, "chance"));

		for (joueur* j : vecJoueur) {
			j->setPartieJoueur(this->nbFigure, figureJoueur);
		}
	}

	void partie::jouer(Diff difficulte) {		
			for (int i = 0; i < this->nbFigure; i++) {
				int nbJoueur = 1;
				for (joueur* f : joueurs) {
					std::cout << "Le joueur " << nbJoueur << " a " << f->getScore() << " points" << std::endl;
					if (difficulte == Diff::facile) {
						f->jouer(joueur::Diff::facile);
					}
					else if (difficulte == Diff::moyen) {
						f->jouer(joueur::Diff::moyen);
					}
					else if (difficulte == Diff::difficile) {
						f->jouer(joueur::Diff::difficile);
					}
					else if (difficulte == Diff::hardcore) {
						f->jouer(joueur::Diff::hardcore);
					}
					std::cout << "Le joueur " << nbJoueur << " fini a " << f->getScore() << " points" << std::endl << std::endl << std::endl;
					nbJoueur++;
				}

			}
			int nbJoueur = 1;
			for (joueur* f : joueurs) {
				std::cout << "Le joueur " << nbJoueur << " a " << f->getScore() << " points " << std::endl;
				nbJoueur++;
			}
	}
}