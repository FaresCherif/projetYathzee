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

		friend class partie; // pour avoir acces � l'enum Diff de cette classe dans la classe partie 
	public:
		joueur(typeJoueur,std::string nom=" ");
		int getScore();
		void lancerDe();
		void afficherValeur();
		void afficherChoixIa(int i);
		void afficherChoixFigure();
		bool isIA();
		void choisirDeJoueur(sf::RenderWindow*);
		void jouer(sf::RenderWindow*, int,bool);
		void choisirFigure(int, int);
		int getNbFigure();
		bool validerFigure(int);
		int entrerNumFigure();
		void setPartieJoueur(const int*, const int*, const int*, std::vector<visibiliteFigure*>, const char*);
		void sauvegarderJoueur();
		strategyDe* getTypeJ();
		int getNbDe();
		int getNbRelance();
		std::vector<visibiliteFigure*> getFigure();
		joueur* charger(int, int, const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE,std::string);
		~joueur();
		joueur& operator=(const joueur&);
		joueur(const joueur&);
		void setFigureNouvellePartie();
		void afficherWindow(sf::RenderWindow*, int);
		int iaRandom();
	};
}