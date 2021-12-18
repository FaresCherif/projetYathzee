#include "partie.h"
#include <vector>
#include <iostream>
#include "nombre.h"
#include "multiple.h"
#include "suite.h"
#include "full.h"
#include "chance.h"
#include <fstream>
#include <sstream>
#include <SFML/Graphics.hpp>


namespace COO {
	partie::partie(std::vector<joueur*> vecJoueur)
	{
		this->joueurs = vecJoueur;


		this->figureJoueur.push_back(new visibiliteFigure(new nombre<1>, "un"));
		this->figureJoueur.push_back(new visibiliteFigure(new nombre<2>, "deux"));
		this->figureJoueur.push_back(new visibiliteFigure(new nombre<3>, "trois"));
		this->figureJoueur.push_back(new visibiliteFigure(new nombre<4>, "quatre"));
		this->figureJoueur.push_back(new visibiliteFigure(new nombre<5>, "cinq"));
		this->figureJoueur.push_back(new visibiliteFigure(new nombre<6>, "six"));
		this->figureJoueur.push_back(new visibiliteFigure(new multiple<3>, "brelan"));
		this->figureJoueur.push_back(new visibiliteFigure(new full, "full"));
		this->figureJoueur.push_back(new visibiliteFigure(new multiple<4>, "carree"));
		this->figureJoueur.push_back(new visibiliteFigure(new suite<4>, "petiteSuite"));
		this->figureJoueur.push_back(new visibiliteFigure(new suite<5>, "grandeSuite"));
		this->figureJoueur.push_back(new visibiliteFigure(new multiple<5>, "yahtzee"));
		this->figureJoueur.push_back(new visibiliteFigure(new chance, "chance"));


		for (joueur* j : this->joueurs) {
			j->setPartieJoueur(&this->nbDe, &this->nbRelance, &this->nbFigure, figureJoueur, SAVE);
		}
	}

	void partie::jouer(sf::RenderWindow* window, int difficulte,bool ecran) {
		for (joueur* j : this->joueurs) { //initialise toutes les figures des joueurs a 0 et non vu
			j->setFigureNouvellePartie();
		}

		for (int i = 0; i < this->nbFigure; i++) {
			int nbJoueur = 1;
			for (joueur* f : joueurs) {
				std::cout << "Le joueur " << f->nom << " a " << f->getScore() << " points" << std::endl;
				
				f->jouer(window, difficulte,ecran);

				std::cout << "Le joueur " << f->nom << " fini a " << f->getScore() << " points" << std::endl << std::endl << std::endl;

				nbJoueur++;
			}

			if (i == 5) {
				std::cout << "-----------Sauvegarde--------------\t\t" << std::endl;

				this->sauvegarder(i + 1);
			}
		}



		
		

		for (joueur* f : joueurs) {
			std::cout << "Le joueur " << f->nom << " a " << f->getScore() << " points " << std::endl;
		}
		
		int i = this->charger();

		std::cout << "-----------Chargement--------------\t\t" << std::endl;

		std::cout << "joueur : " << joueurs.size() << std::endl;;
		for (i; i < this->nbFigure; i++) {

			for (joueur* f : joueurs) {
				std::cout << f->getNbFigure() << " " << f->getFigure().size();
				std::cout << "Le joueur " << f->nom << " a " << f->getScore() << " points" << std::endl;

				f->jouer(window, difficulte,ecran);
				
				std::cout << "Le joueur " << f->nom << " fini a " << f->getScore() << " points" << std::endl << std::endl << std::endl;

			}
		}

		if (ecran) {
			this->ecranFinPartie(window);
		}
		else {
			for (joueur* f : joueurs) {
				std::cout << "Le score final du joueur " << f->nom << " est de " << f->getScore() << std::endl;
				window->close();
			}
		}
	}
	void partie::sauvegarder(int i) //creer notre propre fichier de sauvegarde
	{
		std::ofstream myfile;
		myfile.open(this->SAVE);
		myfile << i << std::endl;

		for (joueur* f : joueurs) {

			f->sauvegarderJoueur();
		}
		myfile.close();

	}
	int partie::charger()
	{
		joueurs.clear();
		std::ifstream fichier(this->SAVE);
		int numTour=0;

		if (fichier)
		{

			std::string ligne;
			int cpt = -1;
			int numIA;
			int pt;
			int ptPrime;
			std::string nom;
			std::vector<visibiliteFigure*> figureJCharger;

			while (getline(fichier, ligne))
			{
				try {
					std::cout << cpt << std::endl;
					if (cpt == -1) {
						int numSave = (stoi(ligne));
						numTour = numSave;
					}
					else if (cpt % 17 == 0) {
						int numSave = (stoi(ligne));
						numIA = numSave;
					}
					else if (cpt % 17 == 1) {
						int numSave = (stoi(ligne));
						pt = numSave;
					}
					else if (cpt % 17 == 2) {
						int numSave = (stoi(ligne));
						ptPrime = numSave;
					}
					else if (cpt % 17 == 3) {
						std::cout << "nom  "<< ligne << std::endl;
						nom = ligne;
					}
					else {

						std::istringstream iss(ligne);
						std::vector<std::string> result;

						for (std::string s; iss >> s;)
							result.push_back(s);
						int n = result.size();

						int boolVu = stoi(result[0]);
						int val = stoi(result[1]);
						int numFig = stoi(result[2]);

						figureJCharger.push_back(new visibiliteFigure(boolVu, val, this->figureJoueur.at(numFig)->getNom(), this->figureJoueur.at(numFig)->getFigure()));


					}
					cpt++;


				}

				catch (...) {
					std::cout << cpt << std::endl;
					joueur* j;
					switch (numIA)
					{
					case 0:
						j = new joueur(typeJoueur::iaMax);
						break;
					case 1:
						j = new joueur(typeJoueur::iaRandom);
						break;
					default:
						j = new joueur(typeJoueur::humain);
						break;
					}
					/*
					std::cout << "ajout joueur" << ligne<<std::endl;
					for (int i = 0; i < figureJCharger.size(); i++) {
						std::cout << figureJCharger.at(i)->getNom()<<std::endl;
					}
					*/
					j->charger(pt, ptPrime, &(this->nbDe), &(this->nbRelance), &(this->nbFigure), figureJCharger, this->SAVE,nom);
					joueurs.push_back(j);
					figureJCharger.clear();
				}
			}
		}
		else
		{
			std::cout << "ERREUR: Impossible d'ouvrir le fichier en lecture." << std::endl;
		}

		return numTour;
	}

	partie::~partie()
	{

		std::cout << "destructeur" << std::endl;
		for (int i = 0; i < this->figureJoueur.size(); ++i) {  //destruction des figures
			if (this->figureJoueur.at(i) != nullptr)
				delete this->figureJoueur.at(i);
		}



		//std::cout <<"partie detruite " << std::endl;
	}

	partie& partie::operator=(const partie& p)
	{
		if (this != &p) {
			for (int i = 0; i < this->figureJoueur.size(); ++i) {
				if (this->figureJoueur.at(i) != nullptr) {
					delete this->figureJoueur.at(i);
				}
			}

			for (int i = 0; i < p.figureJoueur.size(); ++i) {
				if (p.figureJoueur.at(i) != nullptr)
					this->figureJoueur.push_back(new visibiliteFigure(*(p.figureJoueur.at(i))));
				else
					this->figureJoueur.push_back(nullptr);
			}

			this->joueurs = p.joueurs;
		}
		return *this;
	}

	partie::partie(const partie& p)
	{

		this->joueurs = p.joueurs;

		for (int i = 0; i < p.figureJoueur.size(); ++i) {
			if (p.figureJoueur.at(i) != nullptr)
				this->figureJoueur.push_back(new visibiliteFigure(*(p.figureJoueur.at(i))));
			else
				this->figureJoueur.push_back(nullptr);
		}
	}

	void partie::ecranFinPartie(sf::RenderWindow* window)
	{
		std::cout << "boucle fini" << std::endl;

		sf::Texture backgroundTexture;
		backgroundTexture.loadFromFile("image/background.jpg"); //appelle la texture du background

		sf::Sprite backgroundSprite(backgroundTexture);

		float width = (float)window->getSize().x / backgroundTexture.getSize().x;
		float height = (float)window->getSize().y / backgroundTexture.getSize().y;

		backgroundSprite.scale(width, height); // premet de redimensionner le fond selon la taille de la fenetre



		sf::Text text;
		sf::Font font;
		std::vector <sf::Text*> listeTextFinalJoueur;


		font.loadFromFile("font/arial.ttf");
		std::string fin;
		float positionXBoutton = (float)window->getSize().x /2 ; // initioalise la position du premiers boutton des figures
		float positionYButton = 0;

		for (joueur* f : joueurs) {
			fin="Le score final du joueur " + f->nom + " est de ";
			fin.append(std::to_string(f->getScore()));
			text.setString(fin);
			text.setFont(font);
			listeTextFinalJoueur.push_back(new sf::Text(text));
		}

		window->draw(backgroundSprite);

		for (sf::Text* t : listeTextFinalJoueur) {
			t->setPosition(sf::Vector2f(positionXBoutton, positionYButton));
			positionYButton += 50;
			std::cout << t->getString().toAnsiString() << std::endl;
			window->draw(*t);
		}


		window->display();
	}


	// just to backup

}