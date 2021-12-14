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
				std::cout << "Choix aleatoire numero : " << choix+1 << std::endl;
			}
		}
		return choix;
	}

	int joueur::iaMax(){
		int choix=0;
		int valeurMax = -1;	// valeur negatif pour prendre la valeur max disponible avec lese figures actuels

		for (int i = 0; i < nbFigure; i++) {
			if (this->figureActuel[i]->vu == false) {
				if (this->figureActuel[i]->valeur > valeurMax) {
					valeurMax = this->figureActuel[i]->valeur;
					choix = i;
				}
			}
		}

		return choix;
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

	void joueur::setPartieJoueur(int nbFig, std::vector<visibiliteFigure*> visibFig)
	{
		this->nbFigure=nbFig;
		this->figureActuel = visibFig;
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

	bool joueur::validerFigure(int i) {
		if (this->figureActuel[i]->vu == false) {
			this->figureActuel[i]->vu = true;
			this->point += this->figureActuel[i]->valeur;
			

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

	void joueur::jouer(Diff difficulte) {
		int choix = 0;
		choixDeRandom cdr;
		switch (this->typeJ->getType()) {
		case typeJoueur::humain:
			this->choisirDeJoueur();
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
			choix = cdr.choixDe(this->figureActuel, lancerJoueur.getDes());
			break;
		case typeJoueur::iaMax:
			lancerDe();
			choix = iaMax();
			break;
		}
		if (difficulte == Diff::facile)
		{
			this->choisirFigure(choix,Diff::facile);
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

			case Diff::facile :
				if (numChoixFigure >= 0 && numChoixFigure < nbFigure) {
					choixValide = this->validerFigure(numChoixFigure);
				}
				else {
					std::cout << "ERREUR numero non reconnu" << std::endl;
				}
				break;
			case Diff::moyen :
				if (numChoixFigure >= 0 && numChoixFigure < (int)nbFigure / 2) {
					if (numChoixFigure < (int)nbFigure / 2)
					{
						choixValide = this->validerFigure(numChoixFigure);
					}
				}
				else if (numChoixFigure >= (int)nbFigure / 2 && numChoixFigure < nbFigure)
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
			case Diff::difficile :
				if (numChoixFigure >= 0 && numChoixFigure < nbFigure)
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
			case Diff::hardcore :
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

}