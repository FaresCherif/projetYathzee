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
	joueur j1(typeJoueur::iaMax);
	joueur j2(typeJoueur::iaRandom);
	joueur j3(typeJoueur::iaMax);

	std::vector<joueur*> vecJoueurs;
	vecJoueurs.push_back(&j1);
	vecJoueurs.push_back(&j2);
	vecJoueurs.push_back(&j3);

	partie p(vecJoueurs);
	p.jouer();
	return 0;
}
