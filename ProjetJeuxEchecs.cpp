#include "ProjetJeuxEchecs.h"
#include <QMessageBox>
namespace interface {
    ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
        : QMainWindow(parent)
        , ui(new Ui::ProjetJeuxEchecsClass())
    {
        ui->setupUi(this);

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
                boutonsEchiquier[row][col] = button; // 👈 Cette ligne enregistre le bouton
            }
        }

        ajouterRoi(0,4);
        ajouterRoi(7,4);

    }

    void ProjetJeuxEchecs::ajouterRoi(int x, int y) {
        try {
            std::unique_ptr<modele::Roi> roi = std::make_unique<modele::Roi>(modele::Couleur::BLANC, x, y);
            echiquier.ajouterPiece(std::move(roi));
            afficherEchiquier();
        }
        catch (const modele::TropDeRois& e) {
            QMessageBox::warning(this, "Erreur", e.what());
        }
    }


    void ProjetJeuxEchecs::afficherEchiquier()
    {
        // Réinitialise les textes
        for (int row = 0; row < 8; ++row) {
            for (int col = 0; col < 8; ++col) {
                boutonsEchiquier[row][col]->setText("");
            }
        }

        for (const auto& piece : echiquier.getPieces()) {
            auto [x, y] = piece->getPosition();
            boutonsEchiquier[y][x]->setText(QString::fromStdString(piece->getNom()));
        }
    }

    ProjetJeuxEchecs::~ProjetJeuxEchecs()
    {
        delete ui;
    };
}