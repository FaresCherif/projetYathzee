#pragma once
#include "joueur.h"

namespace COO {
	class partie {
	private:
		std::vector<joueur*> joueurs;
		const int nbFigure = 13;
		const int nbDe = 5;
		const int nbRelance = 3;
		const char* SAVE = "sauvegardePartie.txt";
		std::vector<visibiliteFigure*> figureJoueur;

	public:
		partie(std::vector<joueur*>);
		void jouer();
		void sauvegarder(int);
		int charger();
		~partie();
		partie& operator=(const partie&);
		partie(const partie&);

	};
}