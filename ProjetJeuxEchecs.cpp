/**
* Programme gérant l'interface graphique et la gestion de celle-ci
* \file ProjetJeuxEchecs.cpp
* \author Sebastian Crête et Stella Pastor
* \date 26 avril 2025
* Créé le 3 avril 2025
**/

#include "ProjetJeuxEchecs.h"
namespace interface {
    ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
        : QMainWindow(parent), ui(new Ui::ProjetJeuxEchecsClass()) {
        ui->setupUi(this);

        // Creation du menu
        QMenuBar* menuBar = new QMenuBar(this);
        QMenu* menuJeu = menuBar->addMenu("Jeu");

        if (!statusBar()) {
            setStatusBar(new QStatusBar(this));
        }

        QAction* actionNouvellePartie = menuJeu->addAction("Nouvelle partie");
        QAction* actionQuitter = menuJeu->addAction("Quitter");

        connect(actionNouvellePartie, &QAction::triggered, this, &ProjetJeuxEchecs::onNouvellePartie);
        connect(actionQuitter, &QAction::triggered, this, &ProjetJeuxEchecs::onQuitter);

        this->setMenuBar(menuBar);

        // Initialisation de l'echiquier
        boutonsEchiquier.resize(8);
        for (int row = 0; row < 8; ++row) {
            boutonsEchiquier[row].resize(8);
            for (int col = 0; col < 8; ++col) {
                QPushButton* button = new QPushButton(this);
                button->setMinimumSize(80, 80);
                button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

                QString color = (row + col) % 2 == 0 ? "#f0d9b5" : "#b58863";
                button->setStyleSheet(QString("background-color: %1;").arg(color));

                ui->gridLayout->addWidget(button, row, col);
                boutonsEchiquier[row][col] = button;
                connect(button, &QPushButton::clicked, this, &ProjetJeuxEchecs::onCaseClicked);
            }
        }

        initPartie();
    }

    void ProjetJeuxEchecs::initPartie() {
        echiquier.reset();
        ajouterRoi(0, 4, modele::Couleur::NOIR);
        ajouterRoi(7, 4, modele::Couleur::BLANC);

        ajouterTour(0, 0, modele::Couleur::NOIR);
        ajouterTour(0, 7, modele::Couleur::NOIR);
        ajouterTour(7, 0, modele::Couleur::BLANC);
        ajouterTour(7, 7, modele::Couleur::BLANC);

        ajouterCavalier(0, 1, modele::Couleur::NOIR);
        ajouterCavalier(0, 6, modele::Couleur::NOIR);
        ajouterCavalier(7, 1, modele::Couleur::BLANC);
        ajouterCavalier(7, 6, modele::Couleur::BLANC);

        ajouterFou(0, 2, modele::Couleur::NOIR);
        ajouterFou(0, 5, modele::Couleur::NOIR);
        ajouterFou(7, 2, modele::Couleur::BLANC);
        ajouterFou(7, 5, modele::Couleur::BLANC);

        ajouterReine(0, 3, modele::Couleur::NOIR);
        ajouterReine(7, 3, modele::Couleur::BLANC);

        for (int col = 0; col < 8; ++col) {
            ajouterPion(1, col, modele::Couleur::NOIR);
            ajouterPion(6, col, modele::Couleur::BLANC);
        }

        tourActuel = modele::Couleur::BLANC;
        pieceSelectionnee = nullptr;

        afficherEchiquier();
       statusBar()->showMessage("Tour des blancs");
    }

    void ProjetJeuxEchecs::onCaseClicked() {
        QPushButton* button = qobject_cast<QPushButton*>(sender());
        if (!button) return;

        //Trouver les coords du bouton 
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                if (boutonsEchiquier[row][col] == button) {
                    gererClicCase(col, row);
                    return;
                }
            }
        }
    }

    void ProjetJeuxEchecs::gererClicCase(int x, int y) {
        const modele::Piece* piece = echiquier.getPieceAt(x, y);

        if (pieceSelectionnee == nullptr) {
            // Selectionner une piece
            if (piece && piece->getCouleur() == tourActuel) {
                pieceSelectionnee = const_cast<modele::Piece*>(piece);
                positionSelectionnee = { x, y };

                // Mise en evidence
                boutonsEchiquier[y][x]->setStyleSheet(
                    "background-color: #ffcc00;"
                    "border: 2px solid #ff0000;"
                );
            }
        }
        else {
            // Tentative de deplacement
            if (piece && piece->getCouleur() == tourActuel) {
                // Changer la selection
                boutonsEchiquier[positionSelectionnee.second][positionSelectionnee.first]->setStyleSheet(
                    (positionSelectionnee.first + positionSelectionnee.second) % 2 == 0 ?
                    "background-color: #f0d9b5;" : "background-color: #b58863;"
                );

                pieceSelectionnee = const_cast<modele::Piece*>(piece);
                positionSelectionnee = { x, y };

                boutonsEchiquier[y][x]->setStyleSheet(
                    "background-color: #ffcc00;"
                    "border: 2px solid #ff0000;"
                );
            }
            else {
                // Essayer de deplacer la piece
                if (echiquier.deplacerPiece(positionSelectionnee.first, positionSelectionnee.second, x, y)) {
                    // Reinitialiser la selection
                    boutonsEchiquier[positionSelectionnee.second][positionSelectionnee.first]->setStyleSheet(
                        (positionSelectionnee.first + positionSelectionnee.second) % 2 == 0 ?
                        "background-color: #f0d9b5;" : "background-color: #b58863;"
                    );

                    pieceSelectionnee = nullptr;
                    tourActuel = (tourActuel == modele::Couleur::BLANC) ?
                        modele::Couleur::NOIR : modele::Couleur::BLANC;

                    afficherEchiquier();
                    statusBar()->showMessage(
                        tourActuel == modele::Couleur::BLANC ? "Tour des blancs" : "Tour des noirs");

                    verifierFinPartie();
                }
                else {
                    QMessageBox::warning(this, "Mouvement invalide",
                        "Ce mouvement n'est pas autorisé.");
                }
            }
        }
    }

    void ProjetJeuxEchecs::verifierFinPartie() {
        if (echiquier.estEchecEtMat(modele::Couleur::BLANC)) {
            QMessageBox::information(this, "Fin de partie", "Échec et mat! Les noirs gagnent.");
            initPartie();
        }
        else if (echiquier.estEchecEtMat(modele::Couleur::NOIR)) {
            QMessageBox::information(this, "Fin de partie", "Échec et mat! Les blancs gagnent.");
            initPartie();
        }
        else if (echiquier.estEnEchec(tourActuel == modele::Couleur::BLANC ?
            modele::Couleur::NOIR : modele::Couleur::BLANC)) {
            statusBar()->showMessage(
                (tourActuel == modele::Couleur::BLANC ? "Tour des blancs - Échec!" :
                    "Tour des noirs - Échec!"));
        }
    }

    void ProjetJeuxEchecs::onNouvellePartie() {
        initPartie();
    }

    void ProjetJeuxEchecs::onQuitter() {
        this->close();
    }

    void ProjetJeuxEchecs::ajouterRoi(int x, int y, modele::Couleur couleur) {
        try {
            std::unique_ptr<modele::Roi> roi = std::make_unique<modele::Roi>(couleur, x, y);
            echiquier.ajouterPiece(std::move(roi));
            afficherEchiquier();
        }
        catch (const modele::TropDeRois& e) {
            QMessageBox::warning(this, "Erreur", e.what());
        }
    }

    void ProjetJeuxEchecs::ajouterCavalier(int x, int y, modele::Couleur couleur) {
            std::unique_ptr<modele::Cavalier> cavalier = std::make_unique<modele::Cavalier>(couleur, x, y);
            echiquier.ajouterPiece(std::move(cavalier));
            afficherEchiquier();
    }

    void ProjetJeuxEchecs::ajouterTour(int x, int y, modele::Couleur couleur) {
        std::unique_ptr<modele::Tour> tour = std::make_unique<modele::Tour>(couleur, x, y);
        echiquier.ajouterPiece(std::move(tour));
        afficherEchiquier();
    }

    void ProjetJeuxEchecs::ajouterReine(int x, int y, modele::Couleur couleur) {
        std::unique_ptr<modele::Reine> reine = std::make_unique<modele::Reine>(couleur, x, y);
        echiquier.ajouterPiece(std::move(reine));
        afficherEchiquier();
    }

    void ProjetJeuxEchecs::ajouterFou(int x, int y, modele::Couleur couleur) {
        echiquier.ajouterPiece(std::make_unique<modele::Fou>(couleur, x, y));
        afficherEchiquier();
    }

    void ProjetJeuxEchecs::ajouterPion(int x, int y, modele::Couleur couleur) {
        echiquier.ajouterPiece(std::make_unique<modele::Pion>(couleur, x, y));
        afficherEchiquier();
    }

    void ProjetJeuxEchecs::afficherEchiquier() {
        // Reinitialiser toutes les cases

        static const std::map<std::string, std::pair<QChar, QChar>> pieceSymbols = {
            {"Roi",    {QChar(0x2654), QChar(0x265A)}},  // ♔ (blanc) et ♚ (noir)
            {"Reine",  {QChar(0x2655), QChar(0x265B)}},  // ♕ et ♛
            {"Tour",   {QChar(0x2656), QChar(0x265C)}},  // ♖ et ♜
            {"Fou",    {QChar(0x2657), QChar(0x265D)}},  // ♗ et ♝
            {"Cavalier", {QChar(0x2658), QChar(0x265E)}}, // ♘ et ♞
            {"Pion",   {QChar(0x2659), QChar(0x265F)}}   // ♙ et ♟
        };

        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                QString color = (row + col) % 2 == 0 ? "#f0d9b5" : "#b58863";
                boutonsEchiquier[row][col]->setStyleSheet(
                    QString("background-color: %1; border: none;").arg(color));
                boutonsEchiquier[row][col]->setText("");
            }
        }

        // Afficher les pieces
        for (const auto& piece : echiquier.getPieces()) {
            auto [x, y] = piece->getPosition();
            QString textColor = piece->getCouleur() == modele::Couleur::BLANC
                ? "white"
                : "black";
            QChar symbol;
            auto it = pieceSymbols.find(piece->getNom());
            if (it != pieceSymbols.end()) {
                symbol = piece->getCouleur() == modele::Couleur::BLANC
                    ? it->second.first
                    : it->second.second;
            }
            else {
                symbol = '?'; // Symbole par défaut si pièce non reconnue
            }

            QString style = QString(
                "color: %1; "
                "background-color: %2; "
                "border: none; "
                "font-weight: bold; "
                "font-size: 24px; "
                "qproperty-alignment: 'AlignCenter';")
                .arg(textColor)
                .arg((x + y) % 2 == 0 ? "#f0d9b5" : "#b58863");

            boutonsEchiquier[y][x]->setStyleSheet(style);
            boutonsEchiquier[y][x]->setText(symbol);
        }
    }

    ProjetJeuxEchecs::~ProjetJeuxEchecs()
    {
        delete ui;
    };
}