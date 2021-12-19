#include "choixDeHumain.h"

namespace COO {
	int choixDeHumain::choixDe(std::vector<visibiliteFigure*>, de*,int difficulte) //fonction cree car strategieDe est une interface. Toutes les clsses doivent etre cree
	{
		return 0; 
	}
	choixDeHumain::choixDeHumain() //le constructeur set le type de joueur a humain
	{
		this->type = typeJoueur::humain;
	}

	typeJoueur choixDeHumain::getType() const //retroune le type de strategi suivie
	{
		return strategyDe::getType();
	}

}