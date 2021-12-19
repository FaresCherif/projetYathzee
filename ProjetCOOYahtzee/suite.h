//Fares Cherif

#pragma once
namespace COO {
	template<int T>

	class suite : public figure {
	public:
		int valFigure(de* des) {

			int tab[6] = { 0,0,0,0,0,0 };

			for (int i = 0; i < 5; i++) { //compte le nombre de fois qu'il y a chaque face
				tab[des[i].getValeur() - 1]++;
			}



			int i = 0;
			int suite = 0;



			while (i<6 && suite<T) {
				if (tab[i] == 0) {
					suite = 0;
				}
				else { //calcul la plus longue suite de face
					suite++;
				}
				i++;
			}

			if (suite >= T) {//selon la longueur de la suite
				if (T == 4) {
					return 30;
				}
				else if (T == 5) {
					return 40;
				}
			}
			else {
				return 0;
			}
		}
	};
}