#include "chance.h"
#include "de.h"
#include "figure.h"
#include "full.h"
#include "joueur.h"
#include "lancer.h"
#include "yahtzee.h"
#include <iostream>
#include "partie.h"
#include <vector>

using namespace COO;
int main() {

	int level;

	joueur j1(typeJoueur::humain);
	//joueur j2(typeJoueur::humain);
	std::vector<joueur*> vecJoueurs;
	vecJoueurs.push_back(&j1);
	//vecJoueurs.push_back(&j2);
	partie p(vecJoueurs);
	std::cout << "\t\t****************************************************" << std::endl;
	std::cout << "\t\t*  Bonjour et bienvenue dans votre jeux Yahtzee    * " << std::endl;
	std::cout << "\t\t*  veuillez choisir la difficulte de votre partie  *" << std::endl;
	std::cout << "\t\t*                                                  *" << std::endl;
	std::cout << "\t\t*               1-pour facile                      *" << std::endl;
	std::cout << "\t\t*               2-pour moyen                       *" << std::endl;
	std::cout << "\t\t*               3-pour difficile                   *" << std::endl;
	std::cout << "\t\t*               4-pour hardcore                    *" << std::endl;
	std::cout << "\t\t*                                                  *" << std::endl;
	std::cout << "\t\t***************************************************"<< std::endl;
	std::cin >> level;

	switch (level)
	{
	case 1 :
		p.jouer(Diff::facile);
		break;
	case 2:
		p.jouer(Diff::moyen);
		break;
	case 3:
		p.jouer(Diff::difficile);
		break;
	case 4:
		p.jouer(Diff::hardcore);
		break;
	default:
		std::cout << "veuillez choisir un level existant" << std::endl;

	}
	

	
	
	return 0;
}
