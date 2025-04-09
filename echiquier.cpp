#include "echiquier.hpp"
#include "RAII.hpp"
#include <iostream>
using namespace std;

namespace modele {

	void Echiquier::ajouterPiece(unique_ptr<Piece> piece) {
		pieces.push_back(move(piece));
	}

	void Echiquier::afficher() const {
		for (const auto& piece : pieces) {
			cout << piece->getNom() << " en ("
				<< piece->getPosition().first << ","
				<< piece->getPosition().second << ")" << endl;
		}
	}

	void Echiquier::testerDeplacementTemporaire() {
		for (auto& piece : pieces) {
			try {
				RAII dt(*piece, piece->getPosition().first + 1,
					piece->getPosition().second + 1);
				cout << "Deplacement temporaire effectue" << endl;
			}
			catch (const exception e) {
				cerr << "Erreur: " << e.what() << endl;
			}
		}
	}

	const std::vector<std::unique_ptr<Piece>>& modele::Echiquier::getPieces() const {
		return pieces;
	}

}
