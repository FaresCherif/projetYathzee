#include "joueur.h"

#include "nombre.h"

#include "brelan.h"
#include "full.h"
#include "carree.h"
#include "petiteSuite.h"
#include "grandeSuite.h"
#include "yahtzee.h"
#include "chance.h"
#include "visibiliteFigure.h"
#include <iostream>
#include <string>   
#include <random>


namespace COO {
	joueur::joueur(typeJoueur ia)
	{

		this->point = 0; // instancie le nombre de points a 0
		this->type = ia;
		//ajout de toutes les possibilites dans figure actuel
		std::vector<figure*> un;
		un.push_back(new nombre<1>);
		figureActuel.push_back(new visibiliteFigure(un));

		std::vector<figure*> deux;
		deux.push_back(new nombre<2>);
		figureActuel.push_back(new visibiliteFigure(deux));

		std::vector<figure*> trois;
		trois.push_back(new nombre<3>);
		figureActuel.push_back(new visibiliteFigure(trois));

		std::vector<figure*> quatre;
		quatre.push_back(new nombre<4>);
		figureActuel.push_back(new visibiliteFigure(quatre));

		std::vector<figure*> cinq;
		cinq.push_back(new nombre<5>);
		figureActuel.push_back(new visibiliteFigure(cinq));

		std::vector<figure*> six;
		six.push_back(new nombre<6>);
		figureActuel.push_back(new visibiliteFigure(six));




		std::vector<figure*> vecBrelan;

		vecBrelan.push_back(new brelan<1>);
		vecBrelan.push_back(new brelan<2>);
		vecBrelan.push_back(new brelan<3>);
		vecBrelan.push_back(new brelan<4>);
		vecBrelan.push_back(new brelan<5>);
		vecBrelan.push_back(new brelan<6>);

		figureActuel.push_back(new visibiliteFigure(vecBrelan));



		std::vector<figure*> vecFull;

		vecFull.push_back(new full<1,2>);
		vecFull.push_back(new full<1,3>);
		vecFull.push_back(new full<1,4>);
		vecFull.push_back(new full<1,5>);
		vecFull.push_back(new full<1,6>);

		vecFull.push_back(new full<2,1>);
		vecFull.push_back(new full<2,3>);
		vecFull.push_back(new full<2,4>);
		vecFull.push_back(new full<2,5>);
		vecFull.push_back(new full<2,6>);

		vecFull.push_back(new full<3,1>);
		vecFull.push_back(new full<3,2>);
		vecFull.push_back(new full<3,4>);
		vecFull.push_back(new full<3,5>);
		vecFull.push_back(new full<3,6>);

		vecFull.push_back(new full<4,1>);
		vecFull.push_back(new full<4,2>);
		vecFull.push_back(new full<4,3>);
		vecFull.push_back(new full<4,5>);
		vecFull.push_back(new full<4,6>);

		vecFull.push_back(new full<5,1>);
		vecFull.push_back(new full<5,2>);
		vecFull.push_back(new full<5,3>);
		vecFull.push_back(new full<5,4>);
		vecFull.push_back(new full<5,6>);

		vecFull.push_back(new full<6,1>);
		vecFull.push_back(new full<6,2>);
		vecFull.push_back(new full<6,3>);
		vecFull.push_back(new full<6,4>);
		vecFull.push_back(new full<6,5>);

		figureActuel.push_back(new visibiliteFigure(vecFull));


		std::vector<figure*> vecCarree;

		vecCarree.push_back(new carree<1>);
		vecCarree.push_back(new carree<2>);
		vecCarree.push_back(new carree<3>);
		vecCarree.push_back(new carree<4>);
		vecCarree.push_back(new carree<5>);
		vecCarree.push_back(new carree<6>);

		figureActuel.push_back(new visibiliteFigure(vecCarree));


		std::vector<figure*> vecPetiteSuite;

		vecPetiteSuite.push_back(new petiteSuite<1,2,3,4>);
		vecPetiteSuite.push_back(new petiteSuite<2,3,4,5>);
		vecPetiteSuite.push_back(new petiteSuite<3,4,5,6>);

		figureActuel.push_back(new visibiliteFigure(vecPetiteSuite));


		std::vector<figure*> vecGrandeSuite;

		vecGrandeSuite.push_back(new grandeSuite<1,2,3,4,5>);
		vecGrandeSuite.push_back(new grandeSuite<2,3,4,5,6>);

		figureActuel.push_back(new visibiliteFigure(vecGrandeSuite));


		std::vector<figure*> vecYahtzee;

		vecYahtzee.push_back(new yahtzee<1>);
		vecYahtzee.push_back(new yahtzee<2>);
		vecYahtzee.push_back(new yahtzee<3>);
		vecYahtzee.push_back(new yahtzee<4>);
		vecYahtzee.push_back(new yahtzee<5>);
		vecYahtzee.push_back(new yahtzee<6>);

		figureActuel.push_back(new visibiliteFigure(vecYahtzee));


		std::vector<figure*> vecChance;
		vecChance.push_back(new chance);
		this->figureActuel.push_back(new visibiliteFigure(vecChance));

	}

	int joueur::getScore() {
		return this->point;
	}

	void joueur::lancerDe()
	{
		de* d=this->lancerJoueur.lancerDe();
		int i = 0;
		for (visibiliteFigure *vf : this->figureActuel) // Convertie en solution 3 à la compilation ?
		{
			vf->valeur = 0;
			int cptFigure=0;
			while (vf->vecFigure.size()>cptFigure) {
				int val = vf->vecFigure[cptFigure]->valFigure(d);
				if (val > vf->valeur) {
					vf->valeur = val;
				}
				cptFigure++;
			}
			i++;
		}
		std::cout << std::endl;
	}

	void joueur::afficherValeur() {
		if (this->figureActuel[0]->vu == false) {
			std::cout << "un " << this->figureActuel[0]->valeur << std::endl;
		}
		if (this->figureActuel[1]->vu == false) {
			std::cout << "deux " << this->figureActuel[1]->valeur << std::endl;
		}

		if (this->figureActuel[2]->vu == false) {
			std::cout << "trois " << this->figureActuel[2]->valeur << std::endl;
		}

		if (this->figureActuel[3]->vu == false) {
			std::cout << "quatre " << this->figureActuel[3]->valeur << std::endl;
		}

		if (this->figureActuel[4]->vu == false) {
			std::cout << "cinq " << this->figureActuel[4]->valeur << std::endl;
		}

		if (this->figureActuel[5]->vu == false) {
			std::cout << "six " << this->figureActuel[5]->valeur << std::endl;
		}

		if (this->figureActuel[6]->vu == false) {
			std::cout << "brelan " << this->figureActuel[6]->valeur << std::endl;
		}

		if (this->figureActuel[7]->vu == false) {
			std::cout << "full " << this->figureActuel[7]->valeur << std::endl;
		}

		if (this->figureActuel[8]->vu == false) {
			std::cout << "carree " << this->figureActuel[8]->valeur << std::endl;
		}

		if (this->figureActuel[9]->vu == false) {
			std::cout << "petiteSuite " << this->figureActuel[9]->valeur << std::endl;
		}

		if (this->figureActuel[10]->vu == false) {
			std::cout << "grandeSuite " << this->figureActuel[10]->valeur << std::endl;
		}

		if (this->figureActuel[11]->vu == false) {
			std::cout << "yahtzee " << this->figureActuel[11]->valeur << std::endl;
		}

		if (this->figureActuel[12]->vu == false) {
			std::cout << "chance " << this->figureActuel[12]->valeur << std::endl;
		}

	}

	void joueur::afficherChoixIa(int i) {
		if (i== 0) {
			std::cout << "L'IA a choisis les 1 ";
		}
		if (i == 1) {
			std::cout << "L'IA a choisis les 2 ";
		}
		if (i == 2) {
			std::cout << "L'IA a choisis les 3 ";
		}
		if (i == 3) {
			std::cout << "L'IA a choisis les 4 ";
		}
		if (i == 4) {
			std::cout << "L'IA a choisis les 5";
		}
		if (i == 5) {
			std::cout << "L'IA a choisis les 6";
		}
		if (i == 6) {
			std::cout << "L'IA a choisis le brelan ";
		}
		if (i == 7) {
			std::cout << "L'IA a choisis le full ";
		}
		if (i == 8) {
			std::cout << "L'IA a choisis le carree ";
		}
		if (i == 9) {
			std::cout << "L'IA a choisis la petiteSuite ";
		}
		if (i == 10) {
			std::cout << "L'IA a choisis la grandeSuite ";
		}
		if (i == 11) {
			std::cout << "L'IA a choisis le yahtzee ";
		}
		if (i == 12) {
			std::cout << "L'IA a choisis la chance";
		}
		std::cout << std::endl;
	}

	void joueur::afficherChoixFigure() {
		std::cout << "Que voulez-vous prende ?" << std::endl << "Superieur : ";
		if (this->figureActuel[0]->vu == false) {
			std::cout << "Entrez 1 pour les 1 ";
		}
		if (this->figureActuel[1]->vu == false) {
			std::cout << "Entrez 2 pour les 2 ";
		}
		if (this->figureActuel[2]->vu == false) {
			std::cout << "Entrez 3 pour les 3 ";
		}
		if (this->figureActuel[3]->vu == false) {
			std::cout << "Entrez 4 pour les 4 ";
		}
		if (this->figureActuel[4]->vu == false) {
			std::cout << "Entrez 5 pour les 5";
		}
		if (this->figureActuel[5]->vu == false) {
			std::cout << " Entrez 6 pour les 6";
		}
		std::cout << std::endl;

		std::cout << "Inferieur : ";
		if (this->figureActuel[6]->vu == false) {
			std::cout << "Entrez 7 pour brelan ";
		}
		if (this->figureActuel[7]->vu == false) {
			std::cout << "8 pour full ";
		}
		if (this->figureActuel[8]->vu == false) {
			std::cout << "9 pour carree ";
		}
		if (this->figureActuel[9]->vu == false) {
			std::cout << "10 pour petiteSuite ";
		}
		if (this->figureActuel[10]->vu == false) {
			std::cout << "11 pour grandeSuite ";
		}
		if (this->figureActuel[11]->vu == false) {
			std::cout << "12 pour yahtzee ";
		}
		if (this->figureActuel[12]->vu == false) {
			std::cout << "13 pour chance";
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

		for (int i = 0; i < 13; i++) {
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
		const int nbRelance = 3;
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

		int choix;

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

	void joueur::choisirFigure(int numChoixFigue) {
		bool choixValide = false;

		while (!choixValide) {
				if (numChoixFigue >= 0 && numChoixFigue <= 12) {
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

			this->afficherChoixIa(i);

			return true;
		}
		else {
			std::cout << "ERREUR figure deja choisie"<<std::endl;
		}
		return false;
	}
}