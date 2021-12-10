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
		enum class Diff { facile, moyen, difficile, hardcore };
		friend class partie; // pour avoir acces à l'enum Diff de cette classe dans la classe partie 
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
		void jouer(Diff);
		void choisirFigure(int,Diff);
		bool validerFigure(int);
		int entrerNumFigure();
		void setPartieJoueur(int, std::vector<visibiliteFigure*>);

	};
}