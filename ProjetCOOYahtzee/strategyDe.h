#pragma once

#include "visibiliteFigure.h"


namespace COO {
	enum class typeJoueur { humain, iaRandom, iaMax };

	class strategyDe {
	protected:
		typeJoueur type;
	public:
		virtual int choixDe(std::vector<visibiliteFigure*>,de*,int) = 0;
		virtual typeJoueur getType() const = 0;
	};
}