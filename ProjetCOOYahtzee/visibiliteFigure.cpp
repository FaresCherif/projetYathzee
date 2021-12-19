//Fares Cherif

#include "visibiliteFigure.h"

namespace COO {
	visibiliteFigure::visibiliteFigure(figure* f,std::string nom) //constructeur de visibiliteFigure basique
	{
		this->figureC = f;
		this->valeur = 0;
		this->vu = false;
		this->nomFigure = nom;
	}

	bool visibiliteFigure::getFigureVu() { //retourne si la figure a ete vu
		return this->vu;
	}

	int visibiliteFigure::valeurFigure() { //retourn la valeur de la figure
		return this->valeur;
	}
	visibiliteFigure::visibiliteFigure(visibiliteFigure const& vF) //constructeur par recopie de visibiliteFigure
	{
		this->figureC = vF.figureC;
		this->nomFigure = vF.nomFigure;
		this->valeur = vF.valeur;
		this->vu = vF.vu;
	}

	visibiliteFigure::visibiliteFigure(bool v,int val,std::string nom,figure* fig ) { //constructeur de visibiliteFigure avec la vu et valeur
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

	/*
	visibiliteFigure::~visibiliteFigure()
	{
		std::cout << "destruction de " << this->nomFigure << std::endl;
	}
	*/
}