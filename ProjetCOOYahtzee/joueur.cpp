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




	void joueur::choisirDeJoueur() {
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

	void joueur::jouer() {

		int choix=0;
		choixDeRandom cdr;

		switch (this->typeJ->getType()) {
		case typeJoueur::humain:
			this->choisirDeJoueur();
			choix = entrerNumFigure();
			break;
		case typeJoueur::iaRandom:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel,lancerJoueur.getDes());
			break;
		case typeJoueur::iaMax:
			lancerDe();
			choix = this->typeJ->choixDe(this->figureActuel,lancerJoueur.getDes());
			break;
		}

		this->choisirFigure(choix);
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

	void joueur::choisirFigure(int numChoixFigue) {
		bool choixValide = false;

		while (!choixValide) {
				if (numChoixFigue >= 0 && numChoixFigue < this->getNbFigure()) {
					choixValide = this->validerFigure(numChoixFigue);
				}
				else {
					std::cout << "ERREUR numero non reconnu" << std::endl;
				}

				if (!choixValide) {
					numChoixFigue = entrerNumFigure();
				}
		}
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
}