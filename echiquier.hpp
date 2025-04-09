#pragma once
#include "piece.hpp"
#include <vector>
#include <memory>

namespace modele {

	class Echiquier {
		std::vector<std::unique_ptr<Piece>> pieces;

	public:
		void ajouterPiece(std::unique_ptr<Piece> piece);
		void afficher() const;
		void testerDeplacementTemporaire();
		const std::vector<std::unique_ptr<Piece>>& getPieces() const;
	};
}