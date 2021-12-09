#pragma once
#include "lancer.h"
#include "figure.h"
#include <vector>
#include "visibiliteFigure.h"
#include "strategyDe.h"
#include <list>

namespace COO {

	class joueur {
	private:
		int point;
		int pointPrime = 63;
		const static int nbDe = 5;
		const static int nbRelance = 3;
		std::list<int*> tmp;
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
		void jouer_partie_facile();
		void jouer_partie_moyen();
		void jouer_partie_difficile();
		void jouer_partie_hardcore();
		void choisirFigure_partie_facile(int);
		void choisirFigure_partie_moyen(int);
		void choisirFigure_partie_difficile(int);
		void choisirFigure_partie_hardcore(int);
		bool validerFigure(int);
		int entrerNumFigure();
		void setPartieJoueur(int, std::vector<visibiliteFigure*>);

	};
}