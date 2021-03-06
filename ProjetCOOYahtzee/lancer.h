//Fares Cherif

#pragma once
#include "de.h"

namespace COO {

	class lancer {
	private:
		const static int nbDe = 5;
		de desActuels[nbDe];
	public:
		lancer();
		void garder(int);
		void lacher(int);
		bool isTousGarder();
		bool isAucunGarder();
		void aucunGarder();
		de* lancerDe();
		bool isGarder(int);
		de* getDes();
	};
}