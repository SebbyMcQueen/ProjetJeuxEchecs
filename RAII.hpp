#pragma once
#include "piece.hpp"

namespace modele {

	class RAII {
		Piece& piece;
		int ancienX, ancienY;

	public :
		RAII(Piece& piece, int nouveauX, int nouveauY);
		~RAII();
	};
}