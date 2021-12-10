#include "partie.h"
#include <vector>
#include <iostream>
#include "nombre.h"
#include "multiple.h"
#include "suite.h"
#include "full.h"
#include "chance.h"
#include <fstream>


namespace COO {
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
			j->setPartieJoueur(&this->nbDe,&this->nbRelance,&this->nbFigure, figureJoueur, SAVE);
		}
	}

	void partie::jouer() {
		for (int i = 0; i < this->nbFigure; i++) {
			int nbJoueur = 1;
			for (joueur *f : joueurs) {
				std::cout << "Le joueur "<<nbJoueur<<" a " << f->getScore() << " points" << std::endl;
				f->jouer();
				std::cout << "Le joueur " << nbJoueur << " fini a " << f->getScore() << " points" << std::endl<<std::endl<<std::endl;

				nbJoueur++;
			}

			if (i == 5) {
				this->sauvegarder();
			}
		}

		int nbJoueur = 1;

		for (joueur* f : joueurs) {
			std::cout << "Le joueur " << nbJoueur << " a " << f->getScore()<<" points "<<std::endl;
			nbJoueur++;
		}
	}
	void partie::sauvegarder()
	{
		std::ofstream myfile;
		myfile.open(this->SAVE);
		myfile << this->nbFigure<<std::endl;
		myfile << this->nbDe << std::endl;
		myfile << this->nbRelance << std::endl;
		myfile << this->SAVE << std::endl;

		for (joueur* f : joueurs) {
			
			f->sauvegarderJoueur();
		}
		myfile.close();

	}
}