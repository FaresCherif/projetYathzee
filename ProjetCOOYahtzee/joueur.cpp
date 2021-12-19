#include "joueur.h"
#include "nombre.h"
#include "full.h"
#include "yahtzee.h"
#include "chance.h"
#include "visibiliteFigure.h"
#include <iostream>
#include <string>   
#include <random>
#include "multiple.h"
#include "suite.h"
#include "choixDeRandom.h"
#include "choixDeMax.h"
#include "choixDeHumain.h"
#include <fstream>
#include <SFML/Graphics.hpp>
#include "boutton.h"
#include <chrono>       // std::chrono::system_clock

namespace COO {
	joueur::joueur(typeJoueur ia,std::string n)
	{
		//instancie les differentes attribut a une valeur par defaut
		this->SAVEFILE = "";
		this->nbRelance = 0;
		this->point = 0; // instancie le nombre de points a 0
		this->nbFigure = 0;
		this->nbDe = 0;
		this->nom = n;

		switch (ia) //
		{
		case typeJoueur::humain:
			this->typeJ = new choixDeHumain;
			break;
		case typeJoueur::iaRandom:
			this->typeJ = new choixDeRandom;
			break;
		case typeJoueur::iaMax:
			this->typeJ = new choixDeMax;
			break;
		default:
			this->typeJ = new choixDeHumain;
			break;
		}


		//ajout de toutes les possibilites dans figure actuel
	}

	int joueur::getScore() {
		return this->point;
	}

	void joueur::lancerDe()
	{
		de* d = this->lancerJoueur.lancerDe();
		for (visibiliteFigure* vf : this->figureActuel)
		{
			if (vf->vu == false) {
				vf->valeur = 0;
				int val = vf->figureC->valFigure(d);
				vf->valeur = val;
			}
		}
		std::cout << std::endl;
	}

	void joueur::afficherValeur() {
		if (difficulte == 1) {
			for (int i = 0; i < this->getNbFigure(); i++) {
				if (this->figureActuel[i]->vu == false) {
					std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
				}
			}
		}
		else if (difficulte == 2) {
			if (this->figureActuel[0]->getFigureVu() == true &&
				this->figureActuel[1]->getFigureVu() == true &&
				this->figureActuel[2]->getFigureVu() == true &&
				this->figureActuel[3]->getFigureVu() == true &&
				this->figureActuel[4]->getFigureVu() == true &&
				this->figureActuel[5]->getFigureVu() == true) {

				for (int i = 6; i < this->getNbFigure(); i++) {
					if (this->figureActuel[i]->vu == false) {
						std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
					}
				}
			}
			else {
				for (int i = 0; i < 6; i++) {
					if (this->figureActuel[i]->vu == false) {
						std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
					}
				}
			}
		}
		else if (difficulte == 3 || difficulte==4) {
			int i = 0;
			while (this->figureActuel[i]->vu==true)
			{
				i++;
			}
			std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
		}

	}

	void joueur::afficherChoixIa(int i) {
		std::cout << "L'IA a choisis " << this->figureActuel[i]->nomFigure << std::endl;
		std::cout << std::endl;
	}

	void joueur::afficherChoixFigure() {
		
		std::cout << "Que voulez-vous prende ?" << std::endl << std::endl;
		if (this->difficulte == 1) {
			for (int i = 0; i < this->getNbFigure(); i++) {
				if (this->figureActuel[i]->vu == false) {
					std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
				}

			}
		}
		else if (difficulte == 2) {
			if (this->figureActuel[0]->getFigureVu() == true &&
				this->figureActuel[1]->getFigureVu() == true &&
				this->figureActuel[2]->getFigureVu() == true &&
				this->figureActuel[3]->getFigureVu() == true &&
				this->figureActuel[4]->getFigureVu() == true &&
				this->figureActuel[5]->getFigureVu() == true) {
				for (int i = 6; i < this->getNbFigure(); i++) {
					if (this->figureActuel[i]->vu == false) {
						std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
					}
				}
			}
			else {
				for (int i = 0; i < 6; i++) {
					if (this->figureActuel[i]->vu == false) {
						std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
					}
				}
			}
		}
		else if (this->difficulte == 3 || difficulte==4) {
			int i = 0;
			while (this->figureActuel[i]->vu == true) {
				i++;
			}
			std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
		}
		std::cout << std::endl;
	}

	bool joueur::isIA() {
		return !(this->typeJ->getType() == typeJoueur::humain);
	}


	void joueur::afficherWindow(sf::RenderWindow* window, int relance) {

		lancerDe();

		sf::Texture backgroundTexture;
		std::vector < sf::Texture*> deTexture;

		std::vector <Button*> listeBouttonFigure;

		sf::Text text;
		text.setString(this->nom+ " : "+ std::to_string(this->getScore()));

		sf::Font font;
		font.loadFromFile("font/arial.ttf");
		text.setFont(font);


		float positionXBoutton = (float)window->getSize().x - 300; // initioalise la position du premiers boutton des figures
		float positionYButton = 100;


		for (visibiliteFigure* vf : this->figureActuel) { //ajoute les bouttons dans la liste des bouttons de figures
			std::string nomBoutton;
			nomBoutton.append(vf->nomFigure);
			nomBoutton.append(" ");
			nomBoutton.append(std::to_string(vf->valeur));
			if (vf->vu) {
				listeBouttonFigure.push_back(new Button(positionXBoutton, positionYButton, 250, 50, nomBoutton, sf::Color::Blue));
			}
			else {
				listeBouttonFigure.push_back(new Button(positionXBoutton, positionYButton, 250, 50, nomBoutton, sf::Color::Black));
			}
			positionYButton += 50;
		}

		Button relancerDe((float)window->getSize().x / 2 - 200 / 2, (float)window->getSize().y / 2 - 50 / 2, 200, 50, "Relancer De", sf::Color::Black); // place le boutton relance vers le milieu

		for (int i = 0; i < this->getNbDe(); i++) { // cree une nouvelle texture pour chacun des des
			deTexture.push_back(new sf::Texture());
		}

		backgroundTexture.loadFromFile("image/background.jpg"); //appelle la texture du background


		for (int i = 0; i < this->getNbDe();i++) { // applique l'image sur chacun des des selon la face obtenuz
			std::string s = "image/dice/";
			auto valDe = std::to_string(this->lancerJoueur.getDes()[i].getValeur());
			s += valDe;
			s += ".png";
			deTexture.at(i)->loadFromFile(s);

		}



		sf::Sprite backgroundSprite(backgroundTexture);



		std::vector < sf::Sprite*> deSprite;

		for (int i = 0; i < this->getNbDe(); i++) { //set texture sur les sprite des des
			deSprite.push_back(new sf::Sprite(*deTexture.at(i)));
		}




		deSprite.at(0)->setPosition(sf::Vector2f(50, 100));
		for (int i = 1; i < this->getNbDe(); i++) { //place les des
			deSprite.at(i)->setPosition(sf::Vector2f(deSprite.at(i-1)->getPosition().x + deTexture.at(i-1)->getSize().x, deSprite.at(i-1)->getPosition().y));
		}



		float width = (float)window->getSize().x / backgroundTexture.getSize().x;
		float height = (float)window->getSize().y / backgroundTexture.getSize().y;

		backgroundSprite.scale(width, height); // premet de redimensionner le fond selon la taille de la fenetre

		window->draw(backgroundSprite);
		for (int i = 0; i < this->getNbDe(); i++) { //affiche les des
			window->draw(*deSprite.at(i));
		}









		if (this->difficulte == 1) {
			for (int i = 0; i < this->getNbFigure(); i++) {  //affiche les bouttons des figures
				listeBouttonFigure.at(i)->render(window);
			}
		}
		else if (difficulte == 2) {
			if (this->figureActuel[0]->getFigureVu() == true &&
				this->figureActuel[1]->getFigureVu() == true &&
				this->figureActuel[2]->getFigureVu() == true &&
				this->figureActuel[3]->getFigureVu() == true &&
				this->figureActuel[4]->getFigureVu() == true &&
				this->figureActuel[5]->getFigureVu() == true) {
				for (int i = 0; i < this->getNbFigure(); i++) {
					listeBouttonFigure.at(i)->render(window);	
				}
			}
			else {
				for (int i = 0; i < 6; i++) {
					listeBouttonFigure.at(i)->render(window);	
				}
			}
		}
		else if (this->difficulte == 3 || difficulte == 4) {
			int i = 0;
			while (this->figureActuel[i]->vu == true) {
				listeBouttonFigure.at(i)->render(window);
				i++;
			}
			listeBouttonFigure.at(i)->render(window);
		}







		if (relance < this->getNbRelance()) {
			relancerDe.render(window);
		}
		window->draw(text);

		bool figureChoisis = false;

		window->display();
		while (window->isOpen() && !figureChoisis) {
			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window->close();
				}
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (relancerDe.clicked(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) && relance < this->getNbRelance()) {
						std::cout << "relance" << std::endl;
						afficherWindow(window, relance + 1);
						figureChoisis = true;

					}
					else {
						for (int i = 0; i < this->getNbDe(); i++) {
							if ( deSprite.at(i)->getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>( sf::Mouse::getPosition(*window).y))) {
								if (!this->lancerJoueur.isGarder(i)) {
									this->lancerJoueur.garder(i);
								}
								else {
									this->lancerJoueur.lacher(i);
								}
							}
						}

						for (int i = 0; i < this->getNbFigure(); i++) {
							if (!this->figureActuel.at(i)->vu) {
								if (difficulte == 1) {
									if (listeBouttonFigure.at(i)->getRectangle().getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
										this->choisirFigure(i);
										this->lancerJoueur.aucunGarder();
										figureChoisis = true;
									}
								}

								else if (difficulte == 2) {
									if (listeBouttonFigure.at(i)->getRectangle().getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {
										if (i > 5) {
											if (this->figureActuel[0]->getFigureVu() == true &&
												this->figureActuel[1]->getFigureVu() == true &&
												this->figureActuel[2]->getFigureVu() == true &&
												this->figureActuel[3]->getFigureVu() == true &&
												this->figureActuel[4]->getFigureVu() == true &&
												this->figureActuel[5]->getFigureVu() == true) {

												this->choisirFigure(i);
												this->lancerJoueur.aucunGarder();
												figureChoisis = true;
											}
										}
										else {
											this->choisirFigure(i);
											this->lancerJoueur.aucunGarder();
											figureChoisis = true;
										}
									}
								}
								else if (this->difficulte == 3 || difficulte == 4) {
									int i = 0;
									while (this->figureActuel[i]->vu == true) {
										listeBouttonFigure.at(i)->render(window);
										i++;
									}
									if (listeBouttonFigure.at(i)->getRectangle().getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y)) ){
										this->choisirFigure(i);
										this->lancerJoueur.aucunGarder();
										figureChoisis = true;
									}
								}
							}
						}
					}
				}
			}
		}


	}

	void joueur::choisirDeJoueur(sf::RenderWindow* window) {
		std::cout << "La difficulte est de " << this->difficulte << std::endl;

		if (this->pointPrime > 0) {
			std::cout << "Prime dans " << this->pointPrime << " points" << std::endl;
		}
		else {
			std::cout << "Prime acquise" << std::endl;
		}

		bool relancerDe = true;
		int compteurLance = 1;
		this->lancerJoueur.aucunGarder();

		lancerDe();
		afficherValeur();

		while (compteurLance < this->getNbRelance() && relancerDe) {

			std::cout << "relancer (O/N) " << compteurLance << "/" << this->getNbRelance() << std::endl;

			if (!lancerJoueur.isTousGarder()) {
				std::cout << "garder les des ";
				for (int i = 0; i < this->getNbDe(); i++) {
					if (!lancerJoueur.isGarder(i)) {
						std::cout << i + 1 << ",";
					}
				}
				std::cout << "en appuyant sur le nombre correspondant " << std::endl;
			}

			if (!lancerJoueur.isAucunGarder()) {
				std::cout << "ne plus garder les des ";
				for (int i = 0; i < this->getNbDe(); i++) {
					if (lancerJoueur.isGarder(i)) {
						std::cout << i + 1 << ",";
					}
				}
				std::cout << " en appuyant sur le nombre correspondant " << std::endl;
			}

			std::string reponse;
			std::cin >> reponse;

			if (reponse == "N") {
				relancerDe = false;
			}
			else if (reponse == "1" || reponse == "2" || reponse == "3" || reponse == "4" || reponse == "5") {

				if (!this->lancerJoueur.isGarder(stoi(reponse) - 1)) {
					this->lancerJoueur.garder(stoi(reponse) - 1);
				}
				else {
					this->lancerJoueur.lacher(stoi(reponse) - 1);
				}
			}
			else if (reponse == "O") {

				lancerDe();
				afficherValeur();
				compteurLance++;
			}
			else {
				std::cout << "ERREUR : Charactere non reconnu" << std::endl;
			}
		}


	}




	int joueur::entrerNumFigure() {

		bool numeroValide = false;
		int numChoixFigue;

		while (!numeroValide) {
			afficherChoixFigure();

			std::string choixFigure;
			std::cin >> choixFigure;


			try {
				numChoixFigue = (stoi(choixFigure) - 1);
				numeroValide = true;
			}
			catch (...) {
				std::cout << "ERREUR Charactere non reconnu" << std::endl;
			}
		}

		return numChoixFigue;
	}

	void joueur::setPartieJoueur(const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE)
	{
		this->nbDe = nbD;
		this->nbFigure = nbFig;
		this->nbRelance = nbReroll;
		std::vector<visibiliteFigure*> figureJ;

		for (visibiliteFigure* v : visibFig) {
			figureJ.push_back(new visibiliteFigure(*v));  //necessaire car un simple vecteur de pointeur donne directement fais que les joueurs pointent sur les meme visibiliteFigure
		}
		this->figureActuel = figureJ;
		this->SAVEFILE = SAVE;
	}

	int joueur::getNbFigure() {
		return *(this->nbFigure);
	}
	int joueur::getNbDe() {
		return *(this->nbDe);
	}
	int joueur::getNbRelance() {
		return *(this->nbRelance);
	}

	bool joueur::validerFigure(int i) {
		if (this->figureActuel[i]->vu == false) {
			this->point += this->figureActuel[i]->valeur;
			this->figureActuel[i]->vu = true;


			if (i >= 0 && i <= 5 && this->pointPrime > 0) { //regarde si on est dans la partie superieure et si la pime a deja ete prise
				this->pointPrime -= this->figureActuel[i]->valeur;
				if (this->pointPrime <= 0) {		//ajoute la prime
					this->point += 35;
					std::cout << "---------------------------------------------------------PRIME----------------------------------------" << std::endl;
				}
			}
			if (this->typeJ->getType() != typeJoueur::humain) {
				this->afficherChoixIa(i);
			}


			return true;
		}
		else {
			std::cout << "ERREUR figure deja choisie" << std::endl;
		}
		return false;
	}
	void joueur::sauvegarderJoueur()
	{
		std::ofstream myfile;
		myfile.open(this->SAVEFILE, std::ios_base::app);

		if (this->typeJ->getType() == typeJoueur::iaMax) {
			myfile << 0 << std::endl;
		}
		else if (this->typeJ->getType() == typeJoueur::iaRandom) {
			myfile << 1 << std::endl;
		}
		else if (this->typeJ->getType() == typeJoueur::humain) {
			myfile << 2 << std::endl;
		}
		myfile << this->point << std::endl;
		myfile << this->pointPrime << std::endl;
		myfile << this->nom << std::endl;
		myfile << this->difficulte<< std::endl;

		for (int i = 0; i < this->getNbFigure(); i++) {
			myfile << this->figureActuel[i]->vu << " " << this->figureActuel[i]->valeur << " " << i << std::endl;
		}
		myfile << std::endl;
		myfile.close();
	}

	joueur* joueur::charger(int pt, int ptPrime, const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE,std::string nom,int difficulte) {
		this->point = pt;
		this->nom = nom;
		this->pointPrime = ptPrime;
		this->difficulte = difficulte;
		this->setPartieJoueur(nbD, nbReroll, nbFig, visibFig, SAVE);
		return this;
	}


	strategyDe* joueur::getTypeJ()
	{
		return this->typeJ;
	}

	std::vector<visibiliteFigure*> joueur::getFigure() {
		return this->figureActuel;
	}

	joueur::~joueur() {
		delete this->typeJ;
		for (int i = 0; i < this->figureActuel.size(); i++) {
			delete this->figureActuel.at(i);
		}
	}

	joueur& joueur::operator=(const joueur& j) {
		if (this != &j) {
			for (int i = 0; i < this->figureActuel.size(); ++i) {
				if (this->figureActuel.at(i) != nullptr) {
					delete this->figureActuel.at(i);
				}
			}


			if (j.nbDe != nullptr) {				// si la partie a ete initialise
				this->nbDe = j.nbDe;
				this->nbRelance = j.nbRelance;
				this->nbFigure = j.nbFigure;
				this->lancerJoueur = j.lancerJoueur;
				this->SAVEFILE = j.SAVEFILE;
				this->pointPrime = j.pointPrime;
				for (int i = 0; i < j.figureActuel.size(); ++i) {
					if (j.figureActuel.at(i) != nullptr)
						this->figureActuel.at(i) = new visibiliteFigure(*(j.figureActuel.at(i))); // copie en profondeur
					else
						this->figureActuel.at(i) = nullptr;
				}

			}

			this->point = j.point;

			switch (j.typeJ->getType())
			{
			case typeJoueur::humain:
				this->typeJ = new choixDeHumain;
				break;
			case typeJoueur::iaRandom:
				this->typeJ = new choixDeRandom;
				break;
			case typeJoueur::iaMax:
				this->typeJ = new choixDeMax;
				break;
			default:
				break;
			}

		}
		return *this;
	}

	joueur::joueur(const joueur& j) {
		if (j.nbDe != nullptr) {				// si la partie a ete initialise
			this->nbDe = j.nbDe;
			this->nbRelance = j.nbRelance;
			this->nbFigure = j.nbFigure;
			this->lancerJoueur = j.lancerJoueur;
			this->SAVEFILE = j.SAVEFILE;
			this->pointPrime = j.pointPrime;
			for (int i = 0; i < j.figureActuel.size(); ++i) {
				if (j.figureActuel.at(i) != nullptr)
					this->figureActuel.at(i) = new visibiliteFigure(*(j.figureActuel.at(i))); // copie en profondeur
				else
					this->figureActuel.at(i) = nullptr;
			}
		}
		else {
			this->SAVEFILE = "";
			this->nbRelance = 0;
			this->nbFigure = 0;
			this->nbDe = 0;
		}
		this->point = j.point;
		std::cout << this->typeJ << std::endl;

		switch (j.typeJ->getType())
		{
		case typeJoueur::humain:
			this->typeJ = new choixDeHumain;
			break;
		case typeJoueur::iaRandom:
			this->typeJ = new choixDeRandom;
			break;
		case typeJoueur::iaMax:
			this->typeJ = new choixDeMax;
			break;
		default:
			break;
		}


	}
	void joueur::setFigureNouvellePartie()
	{
		for (visibiliteFigure* f : this->figureActuel) {
			f->valeur = 0;
			f->vu = false;
		}
	}

	void joueur::jouer(sf::RenderWindow* window,bool ecran) {

		int choix = 0;
		choixDeRandom cdr;

		switch (this->typeJ->getType()) {
		case typeJoueur::humain:
			if (ecran) {
				std::cout << "dans joueur avant" << std::endl;
				this->afficherWindow(window,1);
				std::cout << "dans joueur apres" << std::endl;

			}
			else {
				this->choisirDeJoueur(window);
				choix = entrerNumFigure();
			}

			break;
		case typeJoueur::iaRandom:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel, lancerJoueur.getDes(),this->difficulte);
			break;
		case typeJoueur::iaMax:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel, lancerJoueur.getDes(),this->difficulte);
			break;
		}

		if (!ecran || this->isIA()) {
			this->choisirFigure(choix);
		}

	}

	void joueur::choisirFigure(int numChoixFigure) {
		
		std::cout << "choix : "<< numChoixFigure<< " difficulte : "<<this->difficulte << std::endl;


		bool choixValide = false;

		while (!choixValide) {
			switch (this->difficulte) {

			case 1:
				if (numChoixFigure >= 0 && numChoixFigure < this->getNbFigure()) {
					choixValide = this->validerFigure(numChoixFigure);
				}
				else {
					std::cout << "ERREUR numero non reconnu" << std::endl;
				}
				break;
			case 2:
				if (numChoixFigure >= 0 && numChoixFigure < (int)*nbFigure / 2) {
					if (numChoixFigure < (int)*nbFigure / 2)
					{
						choixValide = this->validerFigure(numChoixFigure);
					}
				}
				else if (numChoixFigure >= (int)*nbFigure / 2 && numChoixFigure < *nbFigure)
				{
					if (
						this->figureActuel[0]->getFigureVu() == true &&
						this->figureActuel[1]->getFigureVu() == true &&
						this->figureActuel[2]->getFigureVu() == true &&
						this->figureActuel[3]->getFigureVu() == true &&
						this->figureActuel[4]->getFigureVu() == true &&
						this->figureActuel[5]->getFigureVu() == true) 
					{
						choixValide = this->validerFigure(numChoixFigure);
					}
					else {
						std::cout << "Le level est moyen, il faut commencer par la partie supperieur des figures" << std::endl;
					}

				}
				break;

			case 3:
			case 4:

				if (numChoixFigure >= 0 && numChoixFigure < this->getNbFigure())
				{
					int i = 0;
					while (this->figureActuel[i]->vu == true) {
						i++;
					}

					if (numChoixFigure == i)
					{
						choixValide = this->validerFigure(numChoixFigure);
					}
					else
					{
						if (difficulte == 3) {
							std::cout << "Le level est difficile, il faut choisir les figures de 1 a 13 successivement " << std::endl;
						}
						else {
							std::cout << "Le level est hardcore, il faut choisir les figures dans un ordre aleatoire pregenere " << std::endl;
						}

					}
				}
				break;

			default:
				break;

			}
			if (!choixValide) {
				numChoixFigure = entrerNumFigure();
			}
		}

	}

	int  joueur::iaRandom() {
		int choix;
		bool choixValide = false;

		while (!choixValide) {
			int nbAleatoire;

			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(0, 12); // distribution in range [1, 6]
			nbAleatoire = dist6(rng);

			if (this->figureActuel[nbAleatoire]->vu == false) {
				choix = nbAleatoire;
				choixValide = true;
				std::cout << "Choix aleatoire numero : " << choix + 1 << std::endl;
			}
		}
		return choix;
	}

	void joueur::setDifficulte(int diff) {
		this->difficulte = diff;
	}

	void joueur::randomiserOrdreFigure()
	{
		std::random_device rd;

		std::shuffle(this->figureActuel.begin(), this->figureActuel.end(),rd);

	}

}