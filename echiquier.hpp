#pragma once
#include "piece.hpp"
#include <vector>
#include <memory>
#include <utility>

namespace modele {

    class Echiquier {
    public:
        // Constructeur/destructeur
        Echiquier() = default;
        ~Echiquier() = default;

        void reset() { pieces.clear(); };
        // Gestion des pièces
        void ajouterPiece(std::unique_ptr<Piece> piece);

        // Déplacement et règles du jeu
        bool deplacerPiece(int xDepart, int yDepart, int xArrivee, int yArrivee);
        bool estEnEchec(Couleur couleur) const;
        bool estEchecEtMat(Couleur couleur) const;

        // Accesseurs
        const std::vector<std::unique_ptr<Piece>>& getPieces() const;
        const Piece* getPieceAt(int x, int y) const;

        // Méthodes utilitaires (principalement pour le débogage)
        void afficher() const;
        void testerDeplacementTemporaire();

    private:
        std::vector<std::unique_ptr<Piece>> pieces;

        // Méthodes internes
        bool mouvementMetEnEchec(Couleur couleur, int xDepart, int yDepart,
            int xArrivee, int yArrivee) const;
        bool aMouvementValide(Couleur couleur) const;
        bool cheminLibre(int xDepart, int yDepart, int xArrivee, int yArrivee) const;

        // Empêcher la copie
        Echiquier(const Echiquier&) = delete;
        Echiquier& operator=(const Echiquier&) = delete;
    };

} // namespace modele