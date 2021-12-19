#include "choixDeMax.h"
#include "choixDeHumain.h"


namespace COO {
	int choixDeMax::choixDe(std::vector<visibiliteFigure*> vecFig, de* des,int difficulte) //defini comme l'IA Max choisi son de
	{
		int choix = 0;
		int valeurMax = -1;	// valeur negatif pour prendre la prendre la valeur max disponible avec lese figures actuels

		if (difficulte == 1) {
			for (int i = 0; i < vecFig.size(); i++) { //pour toutes les figures
				if (vecFig[i]->getFigureVu() == false) { // si la figure n'a pas encore ete vu
					if (vecFig[i]->valeurFigure() > valeurMax) { //et que la valeur de la figure est la plus hate vu
						valeurMax = vecFig[i]->valeurFigure();
						choix = i; //on garde le numero de cette figure
					}
				}
			}
		}
		else if (difficulte == 2) {
			if (vecFig[0]->getFigureVu() == true &&
				vecFig[1]->getFigureVu() == true &&
				vecFig[2]->getFigureVu() == true &&
				vecFig[3]->getFigureVu() == true &&
				vecFig[4]->getFigureVu() == true &&
				vecFig[5]->getFigureVu() == true) {

				for (int i = 6; i < vecFig.size(); i++) {
					if (vecFig[i]->getFigureVu() == false) { // si la figure n'a pas encore ete vu
						if (vecFig[i]->valeurFigure() > valeurMax) { //et que la valeur de la figure est la plus hate vu
							valeurMax = vecFig[i]->valeurFigure();
							choix = i; //on garde le numero de cette figure
						}
					}
				}
			}
			else {
				for (int i = 0; i < 6; i++) {
					if (vecFig[i]->getFigureVu() == false) { // si la figure n'a pas encore ete vu
						if (vecFig[i]->valeurFigure() > valeurMax) { //et que la valeur de la figure est la plus hate vu
							valeurMax = vecFig[i]->valeurFigure();
							choix = i; //on garde le numero de cette figure
						}
					}
				}
			}
		}
		else if (difficulte == 3 || difficulte == 4) {
			int i = 0;
			while (vecFig[i]->getFigureVu() == true)
			{
				i++;
			}
			choix = i; //on garde le numero de cette figure

		}
		return choix; //on retourne le numero de la figure avec la plus haute valeur
	}

	choixDeMax::choixDeMax() //constructeur du choix de des Max
	{
		this->type = typeJoueur::iaMax; //le type est iaMax
	}

	typeJoueur choixDeMax::getType() const //retourn le type
	{
		return strategyDe::getType();
	}


}