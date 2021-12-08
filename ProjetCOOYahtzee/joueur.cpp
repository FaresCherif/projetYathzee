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
		for (visibiliteFigure *vf : this->figureActuel) // Convertie en solution 3 à la compilation ?
		{
			vf->valeur = 0;
			int val = vf->figureC->valFigure(d);
			vf->valeur = val;
			
		}
		std::cout << std::endl;
	}

	void joueur::afficherValeur() {
		for (int i = 0; i < nbFigure; i++) {
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

		for (int i = 0; i < nbFigure; i++) {
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

		while (compteurLance < 3 && relancerDe) {
			std::cout << "relancer (O/N) " << compteurLance << "/" << nbRelance << std::endl;

			if (!lancerJoueur.isTousGarder()) {
				std::cout << "garder les des ";
				for (int i = 0; i < this->nbDe; i++) {
					if (!lancerJoueur.isGarder(i)) {
						std::cout << i + 1 << ",";
					}
				}
				std::cout << "en appuyant sur le nombre correspondant " << std::endl;
			}

			if (!lancerJoueur.isAucunGarder()) {
				std::cout << "ne plus garder les des ";
				for (int i = 0; i < this->nbDe; i++) {
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

	void joueur::setPartieJoueur(int nbFig, std::vector<visibiliteFigure*> visibFig)
	{
		this->nbFigure=nbFig;
		this->figureActuel = visibFig;
	}

	void joueur::choisirFigure(int numChoixFigue) {
		bool choixValide = false;

		while (!choixValide) {
				if (numChoixFigue >= 0 && numChoixFigue < nbFigure) {
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
}