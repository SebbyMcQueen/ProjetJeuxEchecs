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

			// Mouvement droit (sans prise)
			if (dy == 0) {
				// Case d'arriv�e doit �tre vide
				if (getPieceAt(x2, y2) != nullptr) {
					return false;
				}

				// Pour mouvement de 2 cases, case interm�diaire doit �tre vide
				if (abs(x2 - x1) == 2) {
					int xInter = (x1 + x2) / 2;
					if (getPieceAt(xInter, y2) != nullptr) {
						return false;
					}
				}
			}
			// Mouvement diagonal (prise)
			else {
				// Doit y avoir une pi�ce adverse � capturer
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

		// Trouver la position du roi de la couleur specifiee
		for (const auto& piece : pieces) {
			if (piece->getNom() == "Roi" && piece->getCouleur() == couleur) {
				positionRoi = piece->getPosition();
				break;
			}
		}

		// Verifier si une piece adverse peut atteindre le roi
		for (const auto& piece : pieces) {
			if (piece->getCouleur() != couleur) {
				// Pour le cavalier, on ne v�rifie pas le chemin
				if (piece->getNom() == "Cavalier") {
					if (piece->estMouvementValide(positionRoi.first, positionRoi.second)) {
						return true;
					}
				}
				// Pour les autres pi�ces, on v�rifie le chemin
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
		// Trouver la piece a deplacer
		const Piece* piece = nullptr;
		for (const auto& p : pieces) {
			if (p->getPosition() == std::make_pair(xDepart, yDepart)) {
				piece = p.get();
				break;
			}
		}
		if (!piece) return true;

		// V�rifier si le mouvement capture la pi�ce qui met en �chec
		const Piece* pieceCible = getPieceAt(xArrivee, yArrivee);
		if (pieceCible && pieceCible->getCouleur() != couleur) {
			// Si on capture une pi�ce adverse, v�rifier si c'est celle qui cause l'�chec
			pair<int, int> positionRoi;
			for (const auto& p : pieces) {
				if (p->getNom() == "Roi" && p->getCouleur() == couleur) {
					positionRoi = p->getPosition();
					break;
				}
			}

			// V�rifier si la pi�ce cible met actuellement le roi en �chec
			if (pieceCible->estMouvementValide(positionRoi.first, positionRoi.second)) {
				if (pieceCible->getNom() != "Cavalier") {
					if (cheminLibre(pieceCible->getPosition().first,
						pieceCible->getPosition().second,
						positionRoi.first,
						positionRoi.second)) {
						// Capturer cette pi�ce enl�ve l'�chec
						return false;
					}
				}
				else {
					// Pour le cavalier, pas besoin de v�rifier le chemin
					return false;
				}
			}
		}

		// Simuler le mouvement normalement pour les autres cas
		try {
			RAII dt(*const_cast<Piece*>(piece), xArrivee, yArrivee);
			return estEnEchec(couleur);
		}
		catch (...) {
			return true;
		}
	}

	bool Echiquier::aMouvementValide(Couleur couleur) const {
		// Pour chaque piece de la couleur donnee
		for (const auto& piece : pieces) {
			if (piece->getCouleur() == couleur) {
				auto [x, y] = piece->getPosition();

				// Verifier tous les mouvements possibles
				for (int i = 0; i < 8; ++i) {
					for (int j = 0; j < 8; ++j) {
						if (piece->estMouvementValide(i, j)) {
							// Verifier les obstructions (sauf pour le cavalier)
							if (piece->getNom() != "Cavalier" && !cheminLibre(x, y, i, j)) {
								continue;
							}

							// Verifier si le mouvement sort de l'�chec
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

		// Ne pas verifier la case d'arriv�e (contiendra peut-etre une piece a capturer)
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