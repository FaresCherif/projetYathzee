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
		const static int nbDe = 5;
		const static int nbRelance = 3;
		int nbFigure;
		lancer lancerJoueur;
		std::vector<visibiliteFigure*> figureActuel;
		strategyDe *typeJ;
	public :
		joueur(typeJoueur);
		int getScore();
		void lancerDe();
		void afficherValeur();
		void afficherChoixIa(int i);
		void afficherChoixFigure();
		bool isIA();
		int iaRandom();
		int iaMax();
		void choisirDeJoueur();
		void jouer();
		void choisirFigure(int);
		bool validerFigure(int);
		int entrerNumFigure();
		void setPartieJoueur(int, std::vector<visibiliteFigure*>);

	};
}