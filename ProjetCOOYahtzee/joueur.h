#pragma once
#include "lancer.h"
#include "figure.h"
#include <vector>
#include "visibiliteFigure.h"

namespace COO {
	enum class typeJoueur { humain, iaRandom, iaMax};

	class joueur {
	private:
		int point;
		int pointPrime = 63;
		const static int nbDe = 5;
		lancer lancerJoueur;
		typeJoueur type;
		std::vector<visibiliteFigure*> figureActuel;
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

	};
}