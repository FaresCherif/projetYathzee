#pragma once
#include <vector>
#include "figure.h"

namespace COO {
	class joueur;
	class visibiliteFigure {
		friend class joueur;
	private:
		bool vu;
		int valeur;
		std::vector<figure*> vecFigure;
	public:
		visibiliteFigure(std::vector<figure*>);
	};

}