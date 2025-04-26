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

	Tour::Tour(Couleur couleur, int x, int y) : Piece(couleur, x, y) {}

	bool Tour::estMouvementValide(int nouveauX, int nouveauY) const {
		return (x == nouveauX || y == nouveauY) && !(x == nouveauX && y == nouveauY);
	}

	Cavalier::Cavalier(Couleur couleur, int x, int y) : Piece(couleur, x, y) {}

	bool Cavalier::estMouvementValide(int nouveauX, int nouveauY) const {
		int dx = abs(nouveauX - x);
		int dy = abs(nouveauY - y);
		return (dx == 2 && dy == 1) || (dx == 1 && dy == 2);
	}

	Reine::Reine(Couleur couleur, int x, int y):Piece(couleur,x,y){}
	bool Reine::estMouvementValide(int nouveauX, int nouveauY)const {
		int dx = abs(nouveauX - x);
		int dy = abs(nouveauY - y);
		return (dx == dy) || (x == nouveauX || y == nouveauY);
	}

	Fou::Fou(Couleur couleur, int x, int y) : Piece(couleur, x, y) {}

	bool Fou::estMouvementValide(int nouveauX, int nouveauY) const {
		int dx = abs(nouveauX - x);
		int dy = abs(nouveauY - y);
		return dx == dy;
	}

	Pion::Pion(Couleur couleur, int x, int y) : Piece(couleur, x, y) {}

	bool Pion::estMouvementValide(int nouveauX, int nouveauY) const {
		int direction = (couleur == Couleur::BLANC) ? -1 : 1;
		int dx = nouveauX - x;
		int dy = nouveauY - y;


		if (dy == 0) {
			if ((couleur == Couleur::BLANC && x == 6) ||
				(couleur == Couleur::NOIR && x == 1)) {
				return (dx == direction || dx == 2 * direction) &&
					dx * direction > 0;
			}
			return dx == direction;
		}
		else if (abs(dy) == 1 && dx == direction) {
			return true;
		}

		return false;
	}

}