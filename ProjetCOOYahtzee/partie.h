#pragma once
#include "joueur.h"
#include <SFML/Graphics.hpp>


namespace COO {
	class partie {
	private:
		enum class Diff { facile, moyen, difficile, hardcore };
		std::vector<joueur*> joueurs;
		const int nbFigure = 13;
		const int nbDe = 5;
		const int nbRelance = 3;
		const char* SAVE = "sauvegardePartie.txt";
		std::vector<visibiliteFigure*> figureJoueur;

	public:
		partie(std::vector<joueur*>);
		void jouer(sf::RenderWindow* window,Diff);
		void sauvegarder(int);
		int charger();
		~partie();
		partie& operator=(const partie&);
		partie(const partie&);

	};
}