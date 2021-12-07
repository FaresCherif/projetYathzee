#include "brelan.h"
#include "carree.h"
#include "chance.h"
#include "de.h"
#include "figure.h"
#include "full.h"
#include "grandeSuite.h"
#include "joueur.h"
#include "lancer.h"
#include "petiteSuite.h"
#include "yahtzee.h"
#include <iostream>
#include "partie.h"
#include <vector>

using namespace COO;
int main() {
	joueur j1(false);
	joueur j2(true);
	std::vector<joueur*> vecJoueurs;
	vecJoueurs.push_back(&j1);
	//vecJoueurs.push_back(&j2);

	partie p(vecJoueurs);
	p.jouer();
	return 0;
}
