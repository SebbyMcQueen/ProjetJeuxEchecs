#pragma once
#include "piece.hpp"
#include <vector>
#include <memory>
#include <utility>

namespace modele {

    class Echiquier {
    public:

        Echiquier() = default;
        ~Echiquier() = default;

        void reset() { pieces.clear(); };

        void ajouterPiece(std::unique_ptr<Piece> piece);


        bool deplacerPiece(int xDepart, int yDepart, int xArrivee, int yArrivee);
        bool estEnEchec(Couleur couleur) const;
        bool estEchecEtMat(Couleur couleur) const;


        const std::vector<std::unique_ptr<Piece>>& getPieces() const;
        const Piece* getPieceAt(int x, int y) const;


        void afficher() const;
        void testerDeplacementTemporaire();

    private:
        std::vector<std::unique_ptr<Piece>> pieces;


        bool mouvementMetEnEchec(Couleur couleur, int xDepart, int yDepart,
            int xArrivee, int yArrivee) const;
        bool aMouvementValide(Couleur couleur) const;
        bool cheminLibre(int xDepart, int yDepart, int xArrivee, int yArrivee) const;

        Echiquier(const Echiquier&) = delete;
        Echiquier& operator=(const Echiquier&) = delete;
    };

} 