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

namespace COO {
	joueur::joueur(typeJoueur ia)
	{

		this->point = 0; // instancie le nombre de points a 0
		this->type = ia;
		//ajout de toutes les possibilites dans figure actuel
		figureActuel.push_back(new visibiliteFigure(new nombre<1>,"un"));

		figureActuel.push_back(new visibiliteFigure(new nombre<2>,"deux"));

		figureActuel.push_back(new visibiliteFigure(new nombre<3>,"trois"));

		figureActuel.push_back(new visibiliteFigure(new nombre<4>,"quatre"));

		figureActuel.push_back(new visibiliteFigure(new nombre<5>,"cinq"));

		figureActuel.push_back(new visibiliteFigure(new nombre<6>,"six"));

		figureActuel.push_back(new visibiliteFigure(new multiple<3>,"brelan"));

		figureActuel.push_back(new visibiliteFigure(new full,"full"));

		figureActuel.push_back(new visibiliteFigure(new multiple<4>,"carree"));

		figureActuel.push_back(new visibiliteFigure(new suite<4>,"petiteSuite"));

		figureActuel.push_back(new visibiliteFigure(new suite<5>,"grandeSuite"));

		figureActuel.push_back(new visibiliteFigure(new multiple<5>,"yahtzee"));

		this->figureActuel.push_back(new visibiliteFigure(new chance,"chance"));

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
		std::cout << "L'IA a choisis "<< this->figureActuel[i]<<std::endl;
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
		return !(this->type==typeJoueur::humain);
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
				std::cout << "num aleatoire : " << choix << std::endl;
			}
		}
		return choix;
	}

	int joueur::iaMax(){
		int choix=0;
		int valeurMax = -1;	// valeur negatif pour prendre la prendre la valeur max disponible avec lese figures actuels

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

	void joueur::jouer() {

		int choix=0;

		switch (this->type) {
		case typeJoueur::humain:
			this->choisirDeJoueur();
			choix = entrerNumFigure();
			break;
		case typeJoueur::iaRandom:
			lancerDe();
			choix = iaRandom();
			break;
		case typeJoueur::iaMax:
			lancerDe();
			choix = iaMax();
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

	void joueur::setNbFigure(int nbFig)
	{
		this->nbFigure=nbFig;
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
			if (this->type != typeJoueur::humain) {
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