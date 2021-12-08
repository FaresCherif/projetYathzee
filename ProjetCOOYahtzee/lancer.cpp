#include "lancer.h"

namespace COO {
	lancer::lancer()
	{

		for (int i = 0; i < this->nbDe; i++) {
			this->desActuels[i] = de(1);
		}

	}
	void lancer::garder(int i)
	{
		this->desActuels[i].garderDe();
	}
	void lancer::lacher(int i)
	{
		this->desActuels[i].lacherDe();
	}

	bool lancer::isTousGarder() {
		bool tousGarder = true;
		for (int i = 0; i < this->nbDe; i++) {
			if (!this->desActuels[i].isGarder()) {
				tousGarder = false;
			}
		}
		return tousGarder;
	}

	bool lancer::isAucunGarder() {
		bool aucunGarder = true;
		for (int i = 0; i < this->nbDe; i++) {
			if (this->desActuels[i].isGarder()) {
				aucunGarder = false;
			}
		}
		return aucunGarder;
	}

	void lancer::aucunGarder() {
		for (int i = 0; i < this->nbDe; i++) {
			this->desActuels[i].lacherDe();
		}
	}

	de* lancer::lancerDe()
	{
		for (int i = 0; i < this->nbDe; i++) {
			//this->desActuels[i].lancerDe();
			this->desActuels[i].afficherValeur();
		}
		return this->desActuels;
	}
	bool lancer::isGarder(int i) {
		return this->desActuels[i].isGarder();
	}
}