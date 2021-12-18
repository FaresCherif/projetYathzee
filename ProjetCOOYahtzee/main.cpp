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
#include "boutton.h"

using namespace COO;
int main() {
	joueur j1(typeJoueur::humain,"harold");
	//joueur j2(typeJoueur::iaMax,"lisa");
	//joueur j3(typeJoueur::iaMax);

	std::vector<joueur*> vecJoueurs;
	std::vector<joueur*> vecVide;

	vecJoueurs.push_back(&j1);
	//vecJoueurs.push_back(&j2);
	//vecJoueurs.push_back(&j3);

	//joueur j4(j3);
	
	//vecJoueurs.push_back(&j4);

	partie p(vecJoueurs);
	std::cout << "parties cree"<<std::endl;

	//p.jouer();




	sf::RenderWindow window(sf::VideoMode(1500, 800, 32), "YAHTZEE");
	window.clear(sf::Color(0, 255, 0));
	sf::Texture backgroundTexture;


	backgroundTexture.loadFromFile("image/background.jpg");
	//just to back up
	

	sf::Sprite backgroundSprite(backgroundTexture);


	float width = (float)window.getSize().x / backgroundTexture.getSize().x;
	float height = (float)window.getSize().y / backgroundTexture.getSize().y;

	backgroundSprite.scale(width, height);

	window.draw(backgroundSprite);

	Button lancerPartie((float)window.getSize().x/2 -200/2, (float)window.getSize().y/2 -50/2,200,50,"Lancer partie",sf::Color::Blue);

	
	lancerPartie.render(&window);



	window.display();
	bool partieEnCours = false;

	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				partieEnCours = lancerPartie.clicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

				if (partieEnCours == true) {


					window.display();
					p.jouer(&window,4,false);

				}
			}
		}
	}

	return 0;
}
