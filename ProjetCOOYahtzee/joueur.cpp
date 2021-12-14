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

namespace COO {
	joueur::joueur(typeJoueur ia)
	{
		this->point = 0; // instancie le nombre de points a 0

		switch (ia)
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

		
		//ajout de toutes les possibilites dans figure actuel
	}

	int joueur::getScore() {
		return this->point;
	}

	void joueur::lancerDe()
	{
		de* d=this->lancerJoueur.lancerDe();
		for (visibiliteFigure *vf : this->figureActuel) 
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
		for (int i = 0; i < this->getNbFigure(); i++) {
			if (this->figureActuel[i]->vu == false) {
				std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
			}
		}

	}

	void joueur::afficherChoixIa(int i) {
		std::cout << "L'IA a choisis "<< this->figureActuel[i]->nomFigure<<std::endl;
		std::cout << std::endl;
	}

	void joueur::afficherChoixFigure() {
		std::cout << "Que voulez-vous prende ?"<<std::endl<<std::endl;

		for (int i = 0; i < this->getNbFigure(); i++) {
			if (this->figureActuel[i]->vu == false) {
				std::cout << "Entrez "<<i+1<<" pour "<<this->figureActuel[i]->nomFigure<<std::endl;
			}
		}
		std::cout << std::endl;
	}

	bool joueur::isIA() {
		return !(this->typeJ->getType()==typeJoueur::humain);
	}


	void joueur::afficherWindow(sf::RenderWindow* window,int relance) {


		sf::Texture backgroundTexture;
		sf::Texture premierDeTexture, deuxiemeDeTexture, troisiemeDeTexture, quatriemeDeTexture, cinquiememDeTexture;
		std::vector < sf::Texture*> deTexture;
		Button relancerDe((float)window->getSize().x / 2 - 200 / 2, (float)window->getSize().y / 2 - 50 / 2, 200, 50, "Relancer De", sf::Color::Black); // place le boutton relance vers le milieu

		deTexture.push_back(&premierDeTexture);
		deTexture.push_back(&deuxiemeDeTexture);
		deTexture.push_back(&troisiemeDeTexture);
		deTexture.push_back(&quatriemeDeTexture);
		deTexture.push_back(&cinquiememDeTexture);

		backgroundTexture.loadFromFile("image/background.jpg");


		for (int i = 0; i < this->getNbDe(); i++) {
			std::string s = "image/dice/";
			auto valDe = std::to_string(this->lancerJoueur.getDes()[i].getValeur());
			s += valDe;
			s += ".png";
			deTexture.at(i)->loadFromFile(s);

		}
		
		

		sf::Sprite backgroundSprite(backgroundTexture);


		sf::Sprite premierDeSprite(premierDeTexture);
		sf::Sprite deuxiemeDeSprite(deuxiemeDeTexture);
		sf::Sprite troisiemeDeSprite(troisiemeDeTexture);
		sf::Sprite quatriemeDeSprite(quatriemeDeTexture);
		sf::Sprite cinquiemeDeSprite(cinquiememDeTexture);

		std::vector < sf::Sprite*> deSprite;
		deSprite.push_back(&premierDeSprite);
		deSprite.push_back(&deuxiemeDeSprite);
		deSprite.push_back(&troisiemeDeSprite);
		deSprite.push_back(&quatriemeDeSprite);
		deSprite.push_back(&cinquiemeDeSprite);



		premierDeSprite.setPosition(sf::Vector2f(50, 100));
		deuxiemeDeSprite.setPosition(sf::Vector2f(premierDeSprite.getPosition().x + premierDeTexture.getSize().x, premierDeSprite.getPosition().y));
		troisiemeDeSprite.setPosition(sf::Vector2f(deuxiemeDeSprite.getPosition().x + deuxiemeDeTexture.getSize().x, deuxiemeDeSprite.getPosition().y));
		quatriemeDeSprite.setPosition(sf::Vector2f(troisiemeDeSprite.getPosition().x + troisiemeDeTexture.getSize().x, troisiemeDeSprite.getPosition().y));
		cinquiemeDeSprite.setPosition(sf::Vector2f(quatriemeDeSprite.getPosition().x + quatriemeDeTexture.getSize().x, quatriemeDeSprite.getPosition().y));


		float width = (float)window->getSize().x / backgroundTexture.getSize().x;
		float height = (float)window->getSize().y / backgroundTexture.getSize().y;

		backgroundSprite.scale(width, height); // premet de redimensionner le fond selon la taille de la fenetre

		window->draw(backgroundSprite);
		window->draw(premierDeSprite);
		window->draw(deuxiemeDeSprite);
		window->draw(troisiemeDeSprite);
		window->draw(quatriemeDeSprite);
		window->draw(cinquiemeDeSprite);

		if (relance<this->getNbRelance()) {
			relancerDe.render(window);
		}

		window->display();
		while (window->isOpen()) {

			sf::Event event;
			while (window->pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window->close();
				}
				else if (event.type == sf::Event::MouseButtonPressed) {
					if (relancerDe.clicked(sf::Vector2f(sf::Mouse::getPosition(*window).x, sf::Mouse::getPosition(*window).y))) {
						lancerDe();
						afficherValeur();
						afficherWindow(window, relance+1);
					}
					else {
						for (int i = 0; i < this->getNbDe(); i++) {

						}
					}
				}
			}
		}
	}

	void joueur::choisirDeJoueur(sf::RenderWindow* window) {
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
		afficherWindow(window, relancerDe);

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
				afficherWindow(window, relancerDe);
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
				afficherWindow(window, compteurLance);
			}
			else {
				std::cout << "ERREUR : Charactere non reconnu" << std::endl;
			}
		}
		afficherWindow(window, false);


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

	void joueur::setPartieJoueur(const int* nbD,const int* nbReroll,const int* nbFig, std::vector<visibiliteFigure*> visibFig,const char* SAVE)
	{
		this->nbDe = nbD;
		this->nbFigure=nbFig;
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


			if (i >= 0 && i <= 5 && this->pointPrime>0) { //regarde si on est dans la partie superieure et si la pime a deja ete prise
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
			std::cout << "ERREUR figure deja choisie"<<std::endl;
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

		for (int i = 0; i < this->getNbFigure(); i++) {
			myfile << this->figureActuel[i]->vu << " " << this->figureActuel[i]->valeur << " " << i << std::endl;
		}
		myfile << std::endl;
		myfile.close();
	}

	joueur* joueur::charger(int pt, int ptPrime,const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE) {
		this->point = pt;
		this->pointPrime = ptPrime;
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

	void joueur::jouer(sf::RenderWindow* window, Diff difficulte) {

		int choix = 0;
		choixDeRandom cdr;

		switch (this->typeJ->getType()) {
		case typeJoueur::humain:
			this->choisirDeJoueur(window);
			if (difficulte == Diff::hardcore)
			{
				choix = iaRandom();
			}
			else {
				choix = entrerNumFigure();
			}
			break;
		case typeJoueur::iaRandom:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel, lancerJoueur.getDes());
			break;
		case typeJoueur::iaMax:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel, lancerJoueur.getDes());
			break;
		}

		if (difficulte == Diff::facile)
		{
			this->choisirFigure(choix, Diff::facile);
		}
		else if (difficulte == Diff::moyen) {
			this->choisirFigure(choix, Diff::moyen);
		}
		else if (difficulte == Diff::difficile) {
			this->choisirFigure(choix, Diff::difficile);
		}
		else if (difficulte == Diff::hardcore) {
			this->choisirFigure(choix, Diff::hardcore);
		}
	}

	void joueur::choisirFigure(int numChoixFigure, Diff difficulte) {

		bool choixValide = false;

		while (!choixValide) {
			switch (difficulte) {

			case Diff::facile:
				if (numChoixFigure >= 0 && numChoixFigure < *nbFigure) {
					choixValide = this->validerFigure(numChoixFigure);
				}
				else {
					std::cout << "ERREUR numero non reconnu" << std::endl;
				}
				break;
			case Diff::moyen:
				if (numChoixFigure >= 0 && numChoixFigure < (int)*nbFigure / 2) {
					if (numChoixFigure < (int)*nbFigure / 2)
					{
						choixValide = this->validerFigure(numChoixFigure);
					}
				}
				else if (numChoixFigure >= (int)*nbFigure / 2 && numChoixFigure < *nbFigure)
				{
					if (
						this->figureActuel[1]->getFigureVu() == 1 &&
						this->figureActuel[2]->getFigureVu() == 1 &&
						this->figureActuel[3]->getFigureVu() == 1 &&
						this->figureActuel[4]->getFigureVu() == 1 &&
						(this->figureActuel[5]->getFigureVu() == 1 || this->figureActuel[6]->getFigureVu() == 1)) {
						choixValide = this->validerFigure(numChoixFigure);
					}
					else {
						std::cout << "Le level est moyen, il faut commencer par la partie supperieur des figures" << std::endl;
					}

				}
				break;
			case Diff::difficile:
				if (numChoixFigure >= 0 && numChoixFigure < *nbFigure)
				{
					if (numChoixFigure == 0)
					{
						choixValide = this->validerFigure(numChoixFigure);
						tmp.push_back(&numChoixFigure);
					}
					else if (tmp.size() == numChoixFigure)
					{
						choixValide = this->validerFigure(numChoixFigure);
						tmp.push_back(&numChoixFigure);
					}
					else
					{
						std::cout << "Le level est difficile, il faut choisir les figures de 1 a 13 successivement " << std::endl;
					}
				}
				break;
			case Diff::hardcore:
				if (this->figureActuel[numChoixFigure]->vu == false) {
					choixValide = this->validerFigure(numChoixFigure);
					choixValide = true;
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

}