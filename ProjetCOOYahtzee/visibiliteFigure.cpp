#include "visibiliteFigure.h"

namespace COO {
	visibiliteFigure::visibiliteFigure(std::vector<figure*> vf)
	{
		this->vecFigure = vf;;
		this->valeur = 0;
		this->vu = false;
	}
}