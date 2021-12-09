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

	joueur j1(typeJoueur::humain);
	//joueur j2(typeJoueur::humain);
	std::vector<joueur*> vecJoueurs;
	vecJoueurs.push_back(&j1);
	//vecJoueurs.push_back(&j2);
	partie p(vecJoueurs);
	p.jouer(Diff::difficile);

	
	
	return 0;
}
