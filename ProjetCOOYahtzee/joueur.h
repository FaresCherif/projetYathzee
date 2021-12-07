#pragma once
#include "lancer.h"
#include "figure.h"
#include <vector>
#include "visibiliteFigure.h"

namespace COO {

	class joueur {
	private:
		int point;
		int pointPrime = 63;
		const static int nbDe = 5;
		lancer lancerJoueur;
		bool ia;
		std::vector<visibiliteFigure*> figureActuel;
	public :
		joueur(bool);
		int getScore();
		void lancerDe();
		void afficherValeur();
		void afficherChoixFigure();
		bool isIA();
		void iaRandom();
		void choisirDeJoueur();
		void jouer();
		void choisirFigure();
		bool validerFigure(int);
	};
}