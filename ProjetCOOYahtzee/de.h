#pragma once

namespace COO {

	class de {
	private:
		int valeur;
		bool garder;
	public:
		de(int, bool);
		de(int);
		de();
		void garderDe();
		void lacherDe();
		void lancerDe();
		void afficherValeur();
		bool isGarder();
		int getValeur();
		bool operator==(const int);
	};
}