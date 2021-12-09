#pragma once
#include "joueur.h"

namespace COO {
	enum class Diff { facile, moyen, difficile, hardcore };

	class partie {
	private:
		std::vector<joueur*> joueurs;
		static const int nbFigure = 13;
	public:
		partie(std::vector<joueur*> vecJoueur);
		void jouer(Diff difficulte);
	};
}