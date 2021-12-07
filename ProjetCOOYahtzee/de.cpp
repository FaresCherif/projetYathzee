#include "de.h"
#include <stdlib.h>
#include <iostream>
#include <random>

namespace COO {
	de::de(int valeurDe, bool garderDe)
	{
		this->valeur = valeurDe;
		this->garder = garderDe;
	}

	de::de(int valeurDe)
	{
		this->valeur = valeurDe;
		this->garder = false;
	}

	de::de()
	{
		this->valeur = 1;
		this->garder = false;
	}

	void de::garderDe() {
		this->garder = true;
	}

	void de::lacherDe() {
		this->garder = false;
	}

	void de::lancerDe()
	{
		if (this->garder==false) {
			std::random_device dev;
			std::mt19937 rng(dev());
			std::uniform_int_distribution<std::mt19937::result_type> dist6(1, 6); // distribution in range [1, 6]
			this->valeur = dist6(rng);
		}
	}

	void de::afficherValeur() {
		std::cout << "valeur " << this->valeur << std::endl;
	}

	bool de::isGarder()
	{
		return this->garder;
	}

	int de::getValeur()
	{
		return this->valeur;
	}

}