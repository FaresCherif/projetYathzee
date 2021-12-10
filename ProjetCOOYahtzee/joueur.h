#pragma once
#include "lancer.h"
#include "figure.h"
#include <vector>
#include "visibiliteFigure.h"
#include "strategyDe.h"

namespace COO {

	class joueur {
	private:
		int point;
		int pointPrime = 63;
		const int* nbDe;
		const int* nbRelance;
		const int *nbFigure;
		lancer lancerJoueur;
		std::vector<visibiliteFigure*> figureActuel;
		strategyDe *typeJ;
		const char* SAVEFILE;
	public :
		joueur(typeJoueur);
		int getScore();
		void lancerDe();
		void afficherValeur();
		void afficherChoixIa(int i);
		void afficherChoixFigure();
		bool isIA();
		void choisirDeJoueur();
		void jouer();
		void choisirFigure(int);
		int getNbFigure();
		bool validerFigure(int);
		int entrerNumFigure();
		void setPartieJoueur(const int*,const int*,const int*, std::vector<visibiliteFigure*>,const char*);
		void sauvegarderJoueur();
		strategyDe* getTypeJ();
		int getNbDe();
		int getNbRelance();
		std::vector<visibiliteFigure*> getFigure();
		joueur* charger(int,int,const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE);
	};
}