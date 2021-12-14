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
	//joueur j1(typeJoueur::humain);
	joueur j2(typeJoueur::humain);
	//joueur j3(typeJoueur::iaMax);

	std::vector<joueur*> vecJoueurs;
	std::vector<joueur*> vecVide;

	//vecJoueurs.push_back(&j1);
	vecJoueurs.push_back(&j2);
	//vecJoueurs.push_back(&j3);

	//joueur j4(j3);
	
	//vecJoueurs.push_back(&j4);

	partie p(vecJoueurs);
	std::cout << "parties cree"<<std::endl;

	//p.jouer();




	sf::RenderWindow window(sf::VideoMode(1500, 800, 32), "YAHTZEE");
	window.clear(sf::Color(0, 255, 0));
	sf::Texture backgroundTexture;
	sf::Texture premierDeTexture,deuxiemeDeTexture,troisiemeDeTexture,quatriemeDeTexture,cinquiememDeTexture;


	backgroundTexture.loadFromFile("image/background.jpg");
	//just to back up
	
	premierDeTexture.loadFromFile("image/dice/1.png");
	deuxiemeDeTexture.loadFromFile("image/dice/1.png");
	troisiemeDeTexture.loadFromFile("image/dice/1.png");
	quatriemeDeTexture.loadFromFile("image/dice/1.png");
	cinquiememDeTexture.loadFromFile("image/dice/1.png");
	

	sf::Sprite backgroundSprite(backgroundTexture);

	
	sf::Sprite premierDeSprite(premierDeTexture);
	sf::Sprite deuxiemeDeSprite(deuxiemeDeTexture);
	sf::Sprite troisiemeDeSprite(troisiemeDeTexture);
	sf::Sprite quatriemeDeSprite(quatriemeDeTexture);
	sf::Sprite cinquiemeDeSprite(cinquiememDeTexture);
	
	
	premierDeSprite.setPosition(sf::Vector2f(50, 100));
	deuxiemeDeSprite.setPosition(sf::Vector2f(premierDeSprite.getPosition().x+premierDeTexture.getSize().x, premierDeSprite.getPosition().y));
	troisiemeDeSprite.setPosition(sf::Vector2f(deuxiemeDeSprite.getPosition().x + deuxiemeDeTexture.getSize().x, deuxiemeDeSprite.getPosition().y));
	quatriemeDeSprite.setPosition(sf::Vector2f(troisiemeDeSprite.getPosition().x + troisiemeDeTexture.getSize().x, troisiemeDeSprite.getPosition().y));
	cinquiemeDeSprite.setPosition(sf::Vector2f(quatriemeDeSprite.getPosition().x + quatriemeDeTexture.getSize().x, quatriemeDeSprite.getPosition().y));
	

	float width = (float)window.getSize().x / backgroundTexture.getSize().x;
	float height = (float)window.getSize().y / backgroundTexture.getSize().y;

	backgroundSprite.scale(width, height);

	window.draw(backgroundSprite);
	/*

	*/
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
					window.draw(backgroundSprite);
					window.draw(premierDeSprite);
					window.draw(deuxiemeDeSprite);
					window.draw(troisiemeDeSprite);
					window.draw(quatriemeDeSprite);
					window.draw(cinquiemeDeSprite);

					window.display();
					p.jouer(&window);

				}
			}
			else if (event.type == sf::Event::Resized) {
				float width = (float)window.getSize().x / backgroundTexture.getSize().x;
				float height = (float)window.getSize().y / backgroundTexture.getSize().y;
				sf::Sprite backgroundSprite(backgroundTexture);
				backgroundSprite.scale(width, height);
				window.draw(backgroundSprite);
				window.display();
			}
		}
	}

	return 0;
}
