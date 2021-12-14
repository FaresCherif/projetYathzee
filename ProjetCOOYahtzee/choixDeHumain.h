#pragma once
#include "strategyDe.h"

namespace COO {
	class choixDeHumain : public strategyDe {
	public:
		int choixDe(std::vector<visibiliteFigure*>, de*);
		choixDeHumain();
		typeJoueur getType() const;
	};
}