//Fares Cherif

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
		this->point = 0; 
		this->nbFigure = 0;
		this->nbDe = 0;
		this->nom = n;

		switch (ia) //set le type de joueur
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

	}

	int joueur::getScore() { //retourne le score actuel du joueur
		return this->point;
	}

	void joueur::lancerDe() //lance les de
	{
		de* d = this->lancerJoueur.lancerDe();
		for (visibiliteFigure* vf : this->figureActuel) 
		{
			if (vf->vu == false) { //si la figure n'a pas encore ete vu
				int val = vf->figureC->valFigure(d);
				vf->valeur = val; //la valeur de la figure correspond au de
			}
		}
		std::cout << std::endl;
	}

	void joueur::afficherValeur() { //affiche les points que donneraient chaque figure
		if (difficulte == 1) {//pour la difficulte 1
			for (int i = 0; i < this->getNbFigure(); i++) { 
				if (this->figureActuel[i]->vu == false) {
					std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
				}
			}
		}
		else if (difficulte == 2) { //pour la difficulte 2
			if (figureSuperieurFini()) { //si toute la partie superieure a ete vue

				for (int i = 6; i < this->getNbFigure(); i++) { //affiche la partie inferieur non vue
					if (this->figureActuel[i]->vu == false) {
						std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
					}
				}
			}
			else {
				for (int i = 0; i < 6; i++) { //affiche la partie superieure non vu
					if (this->figureActuel[i]->vu == false) {
						std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl;
					}
				}
			}
		}
		else if (difficulte == 3 || difficulte==4) { //pour la difficulte 3 ou 4
			int i = 0;
			while (this->figureActuel[i]->vu==true)
			{
				i++;
			}
			std::cout << this->figureActuel[i]->nomFigure << " " << this->figureActuel[i]->valeur << std::endl; //affiche la premiere figure non vu
		}

	}

	void joueur::afficherChoixIa(int i) { //affiche la figure choisis par l'ia
		std::cout << "L'IA a choisis " << this->figureActuel[i]->nomFigure << std::endl;
		std::cout << std::endl;
	}

	void joueur::afficherChoixFigure() { //affiche les choix de figures possible
		
		std::cout << "Que voulez-vous prende ?" << std::endl << std::endl;
		if (this->difficulte == 1) { //si la difficulte est de 1
			for (int i = 0; i < this->getNbFigure(); i++) { // affiche toutes les figures non vu
				if (this->figureActuel[i]->vu == false) {
					std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
				}

			}
		}
		else if (difficulte == 2) {//si la difficulte est de 2
			if (figureSuperieurFini()) { //si toute les figures du superieure ont ete faites
				for (int i = 6; i < this->getNbFigure(); i++) { // affiche les figures de l'inferieur non vu
					if (this->figureActuel[i]->vu == false) {
						std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
					}
				}
			}
			else {
				for (int i = 0; i < 6; i++) { //affiche les figures du superieur non vu
					if (this->figureActuel[i]->vu == false) {
						std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
					}
				}
			}
		}
		else if (this->difficulte == 3 || difficulte==4) {//si la difficulte est de 3 ou 4
			int i = 0;
			while (this->figureActuel[i]->vu == true) { //affiche la premiere figure non vu
				i++;
			}
			std::cout << "Entrez " << i + 1 << " pour " << this->figureActuel[i]->nomFigure << std::endl;
		}
		std::cout << std::endl;
	}

	bool joueur::isIA() { //retourne si le joueur est un ia
		return !(this->typeJ->getType() == typeJoueur::humain);
	}


	void joueur::afficherWindow(sf::RenderWindow* window, int relance) { // fait l'affichage visuel

		lancerDe(); 

		sf::Texture backgroundTexture;
		std::vector < sf::Texture*> deTexture;

		std::vector <Button*> listeBouttonFigure;

		sf::Text text;
		text.setString(this->nom+ " : "+ std::to_string(this->getScore())); //met le nom du joueur avec son score

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
			if (vf->vu) { //change la couleur selon si le bouton est vu ou pas
				listeBouttonFigure.push_back(new Button(positionXBoutton, positionYButton, 250, 50, nomBoutton, sf::Color::Blue));
			}
			else {
				listeBouttonFigure.push_back(new Button(positionXBoutton, positionYButton, 250, 50, nomBoutton, sf::Color::Black));
			}
			positionYButton += 50; // decalage entre les boutons
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
			if (figureSuperieurFini()) { //si toutes les figures superieurs sont vu
				for (int i = 0; i < this->getNbFigure(); i++) { //affiche toutes les figures
					listeBouttonFigure.at(i)->render(window);	
				}
			}
			else {
				for (int i = 0; i < 6; i++) { //affiche les figures superieurs
					listeBouttonFigure.at(i)->render(window);	
				}
			}
		}
		else if (this->difficulte == 3 || difficulte == 4) {
			int i = 0;
			while (this->figureActuel[i]->vu == true) { //affiche les figures vu
				listeBouttonFigure.at(i)->render(window);
				i++;
			}
			listeBouttonFigure.at(i)->render(window); //affiche la premiere figure non vu
		}


		if (relance < this->getNbRelance()) { //si le de peut etre relance
			relancerDe.render(window); //affiche le boutton de relance du de
		}
		window->draw(text);//affiche le joueur avec son score

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
					if (relancerDe.clicked(sf::Vector2f(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) && relance < this->getNbRelance()) { //si le boutton de relance de est clicke relance les des
						std::cout << "relance" << std::endl;
						afficherWindow(window, relance + 1);
						figureChoisis = true;

					}
					else {
						for (int i = 0; i < this->getNbDe(); i++) { 
							if ( deSprite.at(i)->getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>( sf::Mouse::getPosition(*window).y))) { //si un de est clicke
								if (!this->lancerJoueur.isGarder(i)) { //si le de n'etait pas a garder
									this->lancerJoueur.garder(i); //le passe a garder
								}
								else {
									this->lancerJoueur.lacher(i); //le repasse a non garder
								}
							}
						}

						for (int i = 0; i < this->getNbFigure(); i++) {
							if (!this->figureActuel.at(i)->vu) {
								if (difficulte == 1) {
									if (listeBouttonFigure.at(i)->getRectangle().getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) { //si une figure est clicke
										this->choisirFigure(i); //la choisis
										this->lancerJoueur.aucunGarder(); //repasse tous les des a lache
										figureChoisis = true;
									}
								}

								else if (difficulte == 2) {
									if (listeBouttonFigure.at(i)->getRectangle().getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y))) {// si une figure est clicke
										if (i > 5) { // c'est une figure inferieure
											if (figureSuperieurFini()){   //les figures superieurs ont toutes ete faite
												this->choisirFigure(i); //la figure est choisis
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
									while (this->figureActuel[i]->vu == true) { //affiche touts les boutons des figuers deja selectionne
										listeBouttonFigure.at(i)->render(window);
										i++;
									}
									if (listeBouttonFigure.at(i)->getRectangle().getGlobalBounds().contains(static_cast<float>(sf::Mouse::getPosition(*window).x), static_cast<float>(sf::Mouse::getPosition(*window).y)) ){ //si le bouttons selectione est celui de la premiere figure non vu
										this->choisirFigure(i);//la selectionne
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

	void joueur::choisirDeJoueur() { // le joueur choisis quoi faire de ses des
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

		while (compteurLance < this->getNbRelance() && relancerDe) { //tant que l'utilisateur veut relancer et qu'il peut encore relancer

			std::cout << "relancer (O/N) " << compteurLance << "/" << this->getNbRelance() << std::endl;

			if (!lancerJoueur.isTousGarder()) { //affiche les des non gardes
				std::cout << "garder les des ";
				for (int i = 0; i < this->getNbDe(); i++) {
					if (!lancerJoueur.isGarder(i)) {
						std::cout << i + 1 << ",";
					}
				}
				std::cout << "en appuyant sur le nombre correspondant " << std::endl;
			}

			if (!lancerJoueur.isAucunGarder()) { //affiche les des gardes
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

			if (reponse == "N") { //si l'entre correspond a ne plus relancer
				relancerDe = false;
			}
			else if (reponse == "1" || reponse == "2" || reponse == "3" || reponse == "4" || reponse == "5") { //si l'entre correspond a garde un de

				if (!this->lancerJoueur.isGarder(stoi(reponse) - 1)) {
					this->lancerJoueur.garder(stoi(reponse) - 1);
				}
				else {
					this->lancerJoueur.lacher(stoi(reponse) - 1);
				}
			}
			else if (reponse == "O") { //si l'entre correspond a relancer

				lancerDe();
				afficherValeur();
				compteurLance++;
			}
			else {
				std::cout << "ERREUR : Charactere non reconnu" << std::endl;
			}
		}


	}




	int joueur::entrerNumFigure() { //le joueur choisis le numero de la figure qu'il veut selectionner

		bool numeroValide = false;
		int numChoixFigue;

		while (!numeroValide) { //tant que l'entre n'est pas valide
			afficherChoixFigure();

			std::string choixFigure;
			std::cin >> choixFigure;


			try {
				numChoixFigue = (stoi(choixFigure) - 1);//essaye de convertir l'entre en nombre. Si cela echoue affiche une erreur et redemande une entree
				numeroValide = true;
			}
			catch (...) {
				std::cout << "ERREUR Charactere non reconnu" << std::endl;
			}
		}

		return numChoixFigue; //retourne le numero entre
	}

	void joueur::setPartieJoueur(const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE)
	{ //donne au joueur les eleent de la partie
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

	bool joueur::validerFigure(int i) {//regarde si la figure a deja ete choisis
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
			if (this->isIA()) {  //affiche le choix fait si c'est une IA
				this->afficherChoixIa(i);
			}


			return true;
		}
		else {
			std::cout << "ERREUR figure deja choisie" << std::endl;
		}
		return false;
	}

	void joueur::sauvegarderJoueur() //sauvegarde les differente info du joueur dans un fichier
	{
		std::ofstream myfile;
		myfile.open(this->SAVEFILE, std::ios_base::app); // ajoute les info sans effacer les info deja presente dans le fichier

		if (this->typeJ->getType() == typeJoueur::iaMax) { //ajoute le type de joueur dont il s'agit
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

		for (int i = 0; i < this->getNbFigure(); i++) { //ajoute les figure
			myfile << this->figureActuel[i]->vu << " " << this->figureActuel[i]->valeur << " " << i << std::endl;
		}
		myfile << std::endl;
		myfile.close();
	}

	joueur* joueur::charger(int pt, int ptPrime, const int* nbD, const int* nbReroll, const int* nbFig, std::vector<visibiliteFigure*> visibFig, const char* SAVE,std::string nom,int difficulte) { //charge les info des joueurs selon les infos en entre
		this->point = pt;
		this->nom = nom;
		this->pointPrime = ptPrime;
		this->difficulte = difficulte;
		this->setPartieJoueur(nbD, nbReroll, nbFig, visibFig, SAVE);
		return this;
	}


	strategyDe* joueur::getTypeJ() //retourn le type de joueur
	{
		return this->typeJ;
	}

	std::vector<visibiliteFigure*> joueur::getFigure() { //retourne le vecteur des visibiliteFigure
		return this->figureActuel;
	}

	joueur::~joueur() { //destructeur de joueur
		delete this->typeJ;
		for (int i = 0; i < this->figureActuel.size(); i++) {
			delete this->figureActuel.at(i);
		}
	}

	joueur& joueur::operator=(const joueur& j) { //operateur d'affectation
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
				this->nom = j.nom;
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

	joueur::joueur(const joueur& j) { //constructeur par recopie
		if (j.nbDe != nullptr) {				// si la partie a ete initialise
			this->nbDe = j.nbDe;
			this->nbRelance = j.nbRelance;
			this->nbFigure = j.nbFigure;
			this->lancerJoueur = j.lancerJoueur;
			this->SAVEFILE = j.SAVEFILE;
			this->pointPrime = j.pointPrime;
			this->difficulte = j.difficulte;
			this->nom = j.nom;
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
	void joueur::setFigureNouvellePartie() //repasse toute les figures a non vu et a 0
	{
		for (visibiliteFigure* f : this->figureActuel) {
			f->valeur = 0;
			f->vu = false;
		}
	}

	void joueur::jouer(sf::RenderWindow* window,bool ecran) { //un tour du joueur

		int choix = 0;
		choixDeRandom cdr;

		switch (this->typeJ->getType()) {
		case typeJoueur::humain:
			if (ecran) {
				this->afficherWindow(window,1); //choisirFigure est directement appele depuis la fonction
			}
			else {
				this->choisirDeJoueur(); //le joueur choisis ses des finaux
				choix = entrerNumFigure(); //le joueur entre le numero de la figure qu'il veut conserver
			}
			break;
		case typeJoueur::iaRandom:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel, lancerJoueur.getDes(),this->difficulte); //l'ia random choisis sa figure
			break;
		case typeJoueur::iaMax:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel, lancerJoueur.getDes(),this->difficulte); //l'ia max choisis sa figure
			break;
		}

		if (!ecran || this->isIA()) {
			this->choisirFigure(choix);
		}

	}

	void joueur::choisirFigure(int numChoixFigure) { //selon la figure choisis
		
		std::cout << "choix : "<< numChoixFigure<< " difficulte : "<<this->difficulte << std::endl;


		bool choixValide = false;

		while (!choixValide) { 
			switch (this->difficulte) {

			case 1:
				if (numChoixFigure >= 0 && numChoixFigure < this->getNbFigure()) { //si le numero est possible
					choixValide = this->validerFigure(numChoixFigure); //le valide
				}
				else {
					std::cout << "ERREUR numero non reconnu" << std::endl;
				}
				break;
			case 2:
				if (numChoixFigure >= 0 && numChoixFigure < 6) { //si le numero choisis est dans la partie superieur
					choixValide = this->validerFigure(numChoixFigure);
				}
				else if (numChoixFigure >= 6 && numChoixFigure < this->getNbFigure())
				{
					if (figureSuperieurFini())
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

				if (numChoixFigure >= 0 && numChoixFigure < this->getNbFigure())// si le numero de la figure est valide
				{
					int i = 0;
					while (this->figureActuel[i]->vu == true) {
						i++;
					}

					if (numChoixFigure == i) //est que le numero entre est bien le premier numero
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
			if (!choixValide) { // si le choix n'est pas valide redemande un numero
				numChoixFigure = entrerNumFigure();
			}
		}

	}

	

	void joueur::setDifficulte(int diff) { //met la difficulte
		this->difficulte = diff;
		if (diff == 4) { //randomise l'ordre des figures
			this->randomiserOrdreFigure();
		}
	}

	void joueur::randomiserOrdreFigure()//randomise l'ordre des figures
	{
		std::random_device rd;

		std::shuffle(this->figureActuel.begin(), this->figureActuel.end(),rd);

	}

	bool joueur::figureSuperieurFini() { //retourne si toutes les figures superieurs ont ete vus
		if (this->figureActuel[0]->getFigureVu() == true &&
			this->figureActuel[1]->getFigureVu() == true &&
			this->figureActuel[2]->getFigureVu() == true &&
			this->figureActuel[3]->getFigureVu() == true &&
			this->figureActuel[4]->getFigureVu() == true &&
			this->figureActuel[5]->getFigureVu() == true) {
			return true;
		}
		return false;
	}

}