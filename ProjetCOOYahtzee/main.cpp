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

	int difficulte = 1;

	float width = (float)window.getSize().x / backgroundTexture.getSize().x;
	float height = (float)window.getSize().y / backgroundTexture.getSize().y;

	backgroundSprite.scale(width, height);

	window.draw(backgroundSprite);

	Button lancerPartieImage((float)window.getSize().x/2 -200/2, (float)window.getSize().y/2 -50/2,400,50,"Lancer partie en visuel",sf::Color(209,45,54));
	Button lancerPartieTerminal((float)window.getSize().x / 2 - 200 / 2, (float)window.getSize().y / 2 +100 / 2, 400, 50, "Lancer partie en terminal", sf::Color::Blue);

	Button facile((float)window.getSize().x / 4.f , 0.f +20.f, 150, 50, "facile", sf::Color(100, 100, 50));
	Button moyen((float)window.getSize().x / 4.f + 200.f , 0.f + 20.f, 150, 50, "moyen", sf::Color(100, 100, 50));
	Button difficile((float)window.getSize().x /4.f +400.f, 0.f + 20.f, 150, 50, "difficile", sf::Color(100, 100, 50));
	Button hardcore((float)window.getSize().x / 4.f +600.f, 0.f + 20.f, 150, 50, "hardcore", sf::Color(100, 100, 50));

	std::vector <Button> listeBouttonDifficulte;
	listeBouttonDifficulte.push_back(facile);
	listeBouttonDifficulte.push_back(moyen);
	listeBouttonDifficulte.push_back(difficile);
	listeBouttonDifficulte.push_back(hardcore);


	for (Button buton : listeBouttonDifficulte) {
		buton.render(&window);
	}


	lancerPartieImage.render(&window);
	lancerPartieTerminal.render(&window);


	window.display();
	bool partieEnCoursVisuel = false;
	bool partieEnCoursTerminal = false;



	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed) {
				window.close();
			}
			else if (event.type == sf::Event::MouseButtonPressed) {
				partieEnCoursVisuel = lancerPartieImage.clicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));
				partieEnCoursTerminal = lancerPartieTerminal.clicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y));

				if (partieEnCoursVisuel == true) {
					p.jouer(&window,difficulte,true);
				}
				else if (partieEnCoursTerminal == true) {
					window.close();
					p.jouer(&window, difficulte, false);
				}
				else {
					int click = -1;
					for (int i = 0; i < listeBouttonDifficulte.size();i++) {
						if(listeBouttonDifficulte.at(i).clicked(sf::Vector2f(sf::Mouse::getPosition(window).x, sf::Mouse::getPosition(window).y)))
						{
							difficulte = i+1;
							click = i;
						}
					}

				}
			}

		}
	}

	return 0;
}
