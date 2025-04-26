/**
* Programme gérant l'échiquier, les intéractions entre les pièces et la logique de jeu
* \file echiquier.cpp
* \author Sebastian Crête et Stella Pastor
* \date 26 avril 2025
* Créé le 3 avril 2025
**/

#include "echiquier.hpp"
#include "RAII.hpp"
#include <algorithm>
#include <stdexcept>
#include <iostream>
using namespace std;

namespace modele {

	void Echiquier::ajouterPiece(unique_ptr<Piece> piece) {
		for (const auto& p : pieces) {
			if (p->getPosition() == piece->getPosition()) {
				throw std::runtime_error("Case deja occupee");
			}
		}
		pieces.push_back(move(piece));
	}

	bool Echiquier::deplacerPiece(int x1, int y1, int x2, int y2) {
		Piece* piece = nullptr;
		for (const auto& p : pieces) {
			if (p->getPosition() == make_pair(x1, y1)) {
				piece = p.get();
				break;
			}
		}

		if (!piece) return false;

		if (!piece->estMouvementValide(x2, y2)) {
			return false;
		}

		if (piece->getNom() == "Pion") {
			int dy = y2 - y1;

			if (dy == 0) {
				if (getPieceAt(x2, y2) != nullptr) {
					return false;
				}

				if (abs(x2 - x1) == 2) {
					int xInter = (x1 + x2) / 2;
					if (getPieceAt(xInter, y2) != nullptr) {
						return false;
					}
				}
			}

			else {
				const Piece* pieceCible = getPieceAt(x2, y2);
				if (!pieceCible || pieceCible->getCouleur() == piece->getCouleur()) {
					return false;
				}
			}
		}


		if (piece->getNom() != "Cavalier") {
			if (!cheminLibre(x1, y1, x2, y2)) {
				return false;
			}
		}

		if (mouvementMetEnEchec(piece->getCouleur(), x1, y1, x2, y2)) {
			return false;
		}

		auto it = find_if(pieces.begin(), pieces.end(), [x2, y2](const auto& p) {
			return p->getPosition() == make_pair(x2, y2);
			});

		if (it != pieces.end()) {
			if ((*it)->getCouleur() == piece->getCouleur()) {
				return false;
			}
			pieces.erase(it);
		}

		piece->deplacer(x2, y2);
		return true;

	}

	bool Echiquier::estEnEchec(Couleur couleur) const {
		std::pair<int, int> positionRoi;

		for (const auto& piece : pieces) {
			if (piece->getNom() == "Roi" && piece->getCouleur() == couleur) {
				positionRoi = piece->getPosition();
				break;
			}
		}

		for (const auto& piece : pieces) {
			if (piece->getCouleur() != couleur) {
				if (piece->getNom() == "Cavalier") {
					if (piece->estMouvementValide(positionRoi.first, positionRoi.second)) {
						return true;
					}
				}
				else if (piece->estMouvementValide(positionRoi.first, positionRoi.second) &&
					cheminLibre(piece->getPosition().first,
						piece->getPosition().second,
						positionRoi.first,
						positionRoi.second)) {
					return true;
				}
			}
		}

		return false;
	}

	bool Echiquier::estEchecEtMat(Couleur couleur) const {
		if (!estEnEchec(couleur)) {
			return false;
		}

		return !aMouvementValide(couleur);
	}

	const std::vector<std::unique_ptr<Piece>>& modele::Echiquier::getPieces() const {
		return pieces;
	}

	const Piece* Echiquier::getPieceAt(int x, int y) const {
		for (const auto& piece : pieces) {
			if (piece->getPosition() == std::make_pair(x, y)) {
				return piece.get();
			}
		}
		return nullptr;
	}

	bool Echiquier::mouvementMetEnEchec(Couleur couleur, int xDepart, int yDepart,
		int xArrivee, int yArrivee) const {
		const Piece* piece = nullptr;
		for (const auto& p : pieces) {
			if (p->getPosition() == std::make_pair(xDepart, yDepart)) {
				piece = p.get();
				break;
			}
		}
		if (!piece) return true;

		const Piece* pieceCible = getPieceAt(xArrivee, yArrivee);
		if (pieceCible && pieceCible->getCouleur() != couleur) {
			pair<int, int> positionRoi;
			for (const auto& p : pieces) {
				if (p->getNom() == "Roi" && p->getCouleur() == couleur) {
					positionRoi = p->getPosition();
					break;
				}
			}

			if (pieceCible->estMouvementValide(positionRoi.first, positionRoi.second)) {
				if (pieceCible->getNom() != "Cavalier") {
					if (cheminLibre(pieceCible->getPosition().first,
						pieceCible->getPosition().second,
						positionRoi.first,
						positionRoi.second)) {
						return false;
					}
				}
				else {
					return false;
				}
			}
		}

		try {
			RAII dt(*const_cast<Piece*>(piece), xArrivee, yArrivee);
			return estEnEchec(couleur);
		}
		catch (...) {
			return true;
		}
	}

	bool Echiquier::aMouvementValide(Couleur couleur) const {
		for (const auto& piece : pieces) {
			if (piece->getCouleur() == couleur) {
				auto [x, y] = piece->getPosition();
				for (int i = 0; i < 8; ++i) {
					for (int j = 0; j < 8; ++j) {
						if (piece->estMouvementValide(i, j)) {
							if (piece->getNom() != "Cavalier" && !cheminLibre(x, y, i, j)) {
								continue;
							}

							if (!mouvementMetEnEchec(couleur, x, y, i, j)) {
								return true;
							}
						}
					}
				}
			}
		}
		return false;
	}

	bool Echiquier::cheminLibre(int xDepart, int yDepart, int xArrivee, int yArrivee) const {
		int dx = xArrivee - xDepart;
		int dy = yArrivee - yDepart;
		int steps = max(abs(dx), abs(dy));
		dx = (dx > 0) ? 1 : (dx < 0) ? -1 : 0;
		dy = (dy > 0) ? 1 : (dy < 0) ? -1 : 0;

		for (int i = 1; i < steps; ++i) {
			int x = xDepart + dx * i;
			int y = yDepart + dy * i;
			if (getPieceAt(x, y) != nullptr) {
				return false;
			}
		}
		return true;
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
			catch (const std::exception& e) {
				cerr << "Erreur: " << e.what() << endl;
			}
		}
	}
}