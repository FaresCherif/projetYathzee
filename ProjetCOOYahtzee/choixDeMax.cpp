#include "choixDeMax.h"
#include "choixDeHumain.h"


namespace COO {
	int choixDeMax::choixDe(std::vector<visibiliteFigure*> vecFig, de* des)
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

	choixDeMax::choixDeMax()
	{
		this->type = typeJoueur::iaMax;
	}

	typeJoueur choixDeMax::getType() const
	{
		return strategyDe::getType();
	}


}