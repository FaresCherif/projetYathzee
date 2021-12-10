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

	public:
		partie(std::vector<joueur*>);
		void jouer();
		void sauvegarder();
	};
}