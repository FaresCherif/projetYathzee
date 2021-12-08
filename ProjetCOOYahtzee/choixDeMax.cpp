#include "choixDeMax.h"
#include "choixDeHumain.h"


int COO::choixDeMax::choixDe(std::vector<visibiliteFigure*> vecFig, de* des)
{
	int choix = 0;
	int valeurMax = -1;	// valeur negatif pour prendre la prendre la valeur max disponible avec lese figures actuels

	for (int i = 0; i < vecFig.size(); i++) {
		if (vecFig[i]->getFigureVu() == false) {
			if (vecFig[i]->valeurFigure() > valeurMax) {
				valeurMax = vecFig[i]->valeurFigure();
				choix = i;
			}
		}
	}

	return choix;
}

COO::choixDeMax::choixDeMax()
{
	this->type = typeJoueur::iaMax;
}


