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
		bool set = true;
		const int* nbDe;
		const int* nbRelance;
		const int* nbFigure;
		std::list<int*> tmp;
		lancer lancerJoueur;
		std::vector<visibiliteFigure*> figureActuel;
		strategyDe* typeJ;
		const char* SAVEFILE;
		enum class Diff { facile, moyen, difficile, hardcore };
		Diff difficulte_local = Diff::facile; // facile par defaut
		friend class partie; // pour avoir acces à l'enum Diff de cette classe dans la classe partie 
	public:
		joueur(typeJoueur);
		int getScore();
		void lancerDe();
		void afficherValeur();
		void afficherChoixIa(int i);
		void afficherChoixFigure();
		bool isIA();
		void choisirDeJoueur(sf::RenderWindow*);
		void jouer(sf::RenderWindow*, Diff);
		void choisirFigure(int, Diff);
		int getNbFigure();
		bool validerFigure(int);
		int entrerNumFigure();
		void setPartieJoueur(const int*, const int*, const int*, std::vector<visibiliteFigure*>, const char*);
		void sauvegarderJoueur();
		strategyDe* getTypeJ();
		int getNbDe();
		int getNbRelance();
		std::vector<visibiliteFigure*> getFigure();
		joueur* charger(int, int, const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE);
		~joueur();
		joueur& operator=(const joueur&);
		joueur(const joueur&);
		void setFigureNouvellePartie();
		void afficherWindow(sf::RenderWindow*, int);
		int iaRandom();
	};
}