#pragma once
namespace COO {
	template<int T>

	class suite : public figure {
	public:
		int valFigure(de* des) {

			int tab[6] = { 0,0,0,0,0,0 };

			for (int i = 0; i < 5; i++) {
				tab[des[i].getValeur() - 1]++;
			}



			int i = 0;
			int suite = 0;



			while (i<6 && suite<T) {
				if (tab[i] == 0) {
					suite = 0;
				}
				else {
					suite++;
				}
				i++;
			}

			//std::cout << "carre de " << T << " rapporte ";
			if (suite >= T) {
				if (T == 4) {
					return 30;
				}
				else if (T == 5) {
					return 40;
				}
			}
			else {
				//std::cout << "0 points" << std::endl;
				return 0;
			}
		}
	};
}