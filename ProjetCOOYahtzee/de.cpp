//Fares Cherif

#include "de.h"
#include <stdlib.h>
#include <iostream>
#include <random>

namespace COO {
	de::de(int valeurDe, bool garderDe) //constructeur de de  avec une valeur et un boole
	{
		this->valeur = valeurDe;
		this->garder = garderDe;
	}

	de::de(int valeurDe) //constructeur de de  avec la valeur de face du de
	{
		this->valeur = valeurDe;
		this->garder = false;
	}

	de::de() //constructeur de de  par defaut
	{
		this->valeur = 1;
		this->garder = false;
	}

	void de::garderDe() { // indique que le de ne doit pas etre relance
		this->garder = true;
	}

	void de::lacherDe() { // indique que le de doit etre relance
		this->garder = false;
	}

	void de::lancerDe()
	{
		if (this->garder==false) {
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6); // genere un nombre aleatoire entre 1 et 6
			this->valeur = dist6(rng); // affecte cette valeur au de
		}
	}

	void de::afficherValeur() { //affiche la valeur du de
		std::cout << "valeur " << this->valeur << std::endl;
	}

	bool de::isGarder() // indique si est de est garde
	{
		return this->garder;
	}

	int de::getValeur() // retourne la valeur de la face du de
	{
		return this->valeur;
	}

	bool de::operator==(const int num) //indique si la valeur de la face est egale a un int
	{
		if (this->valeur == num) {
			return true;
		}
		else {
			return false;
		}
	}



}