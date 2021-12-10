#include "chance.h"
#include "de.h"
#include "figure.h"
#include "full.h"
#include "joueur.h"
#include "lancer.h"
#include "yahtzee.h"
#include <iostream>
#include "partie.h"
#include <vector>
#include <SFML/Graphics.hpp>
#include <fstream>

using namespace COO;
int main() {
	//joueur j1(typeJoueur::humain);
	joueur j2(typeJoueur::iaRandom);
	joueur j3(typeJoueur::iaMax);

	std::vector<joueur*> vecJoueurs;
	//vecJoueurs.push_back(&j1);
	vecJoueurs.push_back(&j2);
	vecJoueurs.push_back(&j3);

	partie p(vecJoueurs);
	p.jouer();

	sf::RenderWindow window(sf::VideoMode(1500, 800, 32), "YAHTZEE");
	window.clear(sf::Color(0, 255, 0));
	sf::Texture background;

	background.loadFromFile("b.jpg");
	sf::Sprite s(background);
	float width = (float)window.getSize().x / background.getSize().x;
	float height = (float)window.getSize().y / background.getSize().y;
	s.scale(width, height);
	window.draw(s);
	window.display();


	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::Resized) {
				float width = (float)window.getSize().x / background.getSize().x;
				float height = (float)window.getSize().y / background.getSize().y;
				sf::Sprite s(background);
				s.scale(width, height);
				window.draw(s);
				window.display();
			}
		}
	}

	return 0;
}
