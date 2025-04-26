/**
* Programme impl�mentant un processus RAII dans le but de d�tecter la validit� d'un mouvement
* \file RAII.cpp
* \author Sebastian Cr�te et Stella Pastor
* \date 26 avril 2025
* Cr�� le 3 avril 2025
**/

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