#include "piece.hpp"
#include <iostream>
using namespace std;

namespace modele {

	int Roi::compteur = 0;

	Piece::Piece(Couleur couleur, int x, int y):couleur(couleur), x(x), y(y) {}

	void Piece::deplacer(int nouveauX, int nouveauY) {
		x = nouveauX;
		y = nouveauY;
	}

	Roi::Roi(Couleur couleur, int x, int y) : Piece(couleur, x, y) {
		if (compteur >= 2) {
			throw TropDeRois();
		}
		compteur++;
		cout << "Création d'un roi (" << compteur << "/2)" << endl;
	}

	Roi ::~Roi() {
		compteur--;
		cout << "Destruction d'un roi (" << compteur << "/2)" << endl;
	}

	bool Roi::estMouvementValide(int nouveauX, int nouveauY) const {
		int dx = abs(nouveauX - x);
		int dy = abs(nouveauY - y);
		return dx <= 1 && dy <= 1;
	}
}