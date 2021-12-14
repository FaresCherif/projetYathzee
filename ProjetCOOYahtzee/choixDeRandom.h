#pragma once
#include "strategyDe.h"

namespace COO {
	class choixDeRandom : public strategyDe {
	public :
		int choixDe(std::vector<visibiliteFigure*>, de*);
		choixDeRandom();
		typeJoueur getType() const;
	};
}