#include "RAII.hpp"
using namespace std;

namespace modele {

	RAII::RAII(Piece& piece, int nouveauX, int nouveauY) :
		piece(piece), ancienX(piece.getPosition().first),
		ancienY(piece.getPosition().second) {
		piece.deplacer(nouveauX, nouveauY);
	}

	RAII::~RAII() {
		piece.deplacer(ancienX, ancienY);
	}
}