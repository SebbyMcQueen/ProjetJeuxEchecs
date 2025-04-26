/**
* Programme implémentant un processus RAII dans le but de détecter la validité d'un mouvement
* \file RAII.cpp
* \author Sebastian Crête et Stella Pastor
* \date 26 avril 2025
* Créé le 3 avril 2025
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