#pragma once
#include "joueur.h"

namespace COO {
	class partie {
	private:
		std::vector<joueur*> joueurs;
		static const int nbFigure = 13;
	public:
		partie(std::vector<joueur*> vecJoueur);
		void jouer();
	};
}