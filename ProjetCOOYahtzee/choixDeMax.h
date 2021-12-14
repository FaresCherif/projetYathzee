#pragma once
#include "strategyDe.h"

namespace COO {
	class choixDeMax : public strategyDe {
	public :
		int choixDe(std::vector<visibiliteFigure*>, de*);
		choixDeMax();
		typeJoueur getType() const;
	};
}