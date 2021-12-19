#pragma once
#include "strategyDe.h"

namespace COO {
	class choixDeMax : public strategyDe {
	public :
		int choixDe(std::vector<visibiliteFigure*>, de*,int);
		choixDeMax();
		typeJoueur getType() const;
	};
}