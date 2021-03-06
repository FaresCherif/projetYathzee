//Fares Cherif

#pragma once
#include <vector>
#include "figure.h"
#include <iostream>
#include <string>

namespace COO {
	class joueur;
	class visibiliteFigure {
		friend class joueur;
	private:
		bool vu;
		int valeur;
		figure* figureC;
		std::string nomFigure;
	public:
		visibiliteFigure(figure*,std::string);
		bool getFigureVu();
		int valeurFigure();
		visibiliteFigure(visibiliteFigure const&);
		visibiliteFigure(bool v, int val, std::string nom, figure*);
		std::string getNom();
		figure* getFigure();
		//~visibiliteFigure();
	};

}