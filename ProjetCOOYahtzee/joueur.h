#pragma once
#include "lancer.h"
#include "figure.h"
#include <vector>
#include "visibiliteFigure.h"
#include "strategyDe.h"
#include <SFML/Graphics.hpp>
#include <list>

namespace COO {

	class joueur {
	private:
		int point;
		int pointPrime = 63;
		const int* nbDe;
		const int* nbRelance;
		const int* nbFigure;
		std::list<int*> tmp;
		lancer lancerJoueur;
		std::vector<visibiliteFigure*> figureActuel;
		strategyDe* typeJ;
		const char* SAVEFILE;
		std::string nom;
		int difficulte;

		friend class partie; // pour avoir acces à l'enum Diff de cette classe dans la classe partie 
	public:
		joueur(typeJoueur,std::string nom=" ");
		void lancerDe();
		void afficherValeur();
		void afficherChoixIa(int i);
		void afficherChoixFigure();
		void choisirDeJoueur(sf::RenderWindow*);
		void jouer(sf::RenderWindow*,bool);
		void choisirFigure(int);
		bool validerFigure(int);
		int entrerNumFigure();
		void setPartieJoueur(const int*, const int*, const int*, std::vector<visibiliteFigure*>, const char*);
		void sauvegarderJoueur();

		std::vector<visibiliteFigure*> getFigure();
		joueur* charger(int, int, const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE,std::string);
		~joueur();
		joueur& operator=(const joueur&);
		joueur(const joueur&);
		void setFigureNouvellePartie();
		void afficherWindow(sf::RenderWindow*, int);
		int iaRandom();
		void randomiserOrdreFigure();



		bool isIA();
		int getScore();
		int getNbFigure();
		int getNbDe();
		int getNbRelance();
		strategyDe* getTypeJ();

		void setDifficulte(int);

	};
}