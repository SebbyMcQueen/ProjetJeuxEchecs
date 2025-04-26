#pragma once

#include <QtWidgets/QMainWindow>
#include <QMessageBox>
#include "ui_ProjetJeuxEchecs.h"
#include <QPushButton>
#include <qmenu.h>
#include <qstatusbar.h>
#include <qmenubar.h>
#include "echiquier.hpp"
#include "piece.hpp"
#include <vector>
#include <memory>
#include <iostream>

QT_BEGIN_NAMESPACE
namespace Ui { class ProjetJeuxEchecsClass; };
QT_END_NAMESPACE

namespace interface {

    class ProjetJeuxEchecs : public QMainWindow
    {
        Q_OBJECT

    public:
        ProjetJeuxEchecs(QWidget* parent = nullptr);
        ~ProjetJeuxEchecs();

    private slots:
        void onCaseClicked();
        void onNouvellePartie();
        void onQuitter();
    private:
        Ui::ProjetJeuxEchecsClass* ui;
        modele::Echiquier echiquier;
        std::vector<std::vector<QPushButton*>> boutonsEchiquier;
        modele::Couleur tourActuel = modele::Couleur::BLANC;
        modele::Piece* pieceSelectionnee = nullptr;
        std::pair<int, int> positionSelectionnee;

        void initPartie();
        void verifierFinPartie();
        void afficherEchiquier();
        void gererClicCase(int x, int y);
        void ajouterRoi(int x, int y, modele::Couleur couleur);
        void ajouterTour(int x, int y, modele::Couleur couleur);
        void ajouterCavalier(int x, int y, modele::Couleur couleur);
        void ajouterReine(int x, int y, modele::Couleur couleur);
        void ajouterFou(int x, int y, modele::Couleur couleur);
        void ajouterPion(int x, int y, modele::Couleur couleur);
    };
}