#include "visibiliteFigure.h"

namespace COO {
	visibiliteFigure::visibiliteFigure(figure* f,std::string nom)
	{
		this->figureC = f;
		this->valeur = 0;
		this->vu = false;
		this->nomFigure = nom;
	}

	bool visibiliteFigure::getFigureVu() {
		return this->vu;
	}

	int visibiliteFigure::valeurFigure() {
		return this->valeur;
	}
}