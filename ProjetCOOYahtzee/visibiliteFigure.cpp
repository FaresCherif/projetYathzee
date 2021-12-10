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
	visibiliteFigure::visibiliteFigure(visibiliteFigure const& vF)
	{
		this->figureC = vF.figureC;
		this->nomFigure = vF.nomFigure;
		this->valeur = vF.valeur;
		this->vu = vF.vu;
	}

	visibiliteFigure::visibiliteFigure(bool v,int val,std::string nom,figure* fig ) {
		this->vu = v;
		this->valeur = val;
		this->nomFigure = nom;
		this->figureC = fig;
	}

	std::string visibiliteFigure::getNom() {
		return this->nomFigure;
	}

	figure* visibiliteFigure::getFigure() {
		return this->figureC;
	}
}