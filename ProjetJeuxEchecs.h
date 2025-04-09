#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_ProjetJeuxEchecs.h"
#include <QPushButton>
#include "echiquier.hpp"
#include "piece.hpp"
#include <vector>
#include <memory>

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

    private:
        Ui::ProjetJeuxEchecsClass* ui;
        modele::Echiquier echiquier;
        std::vector<std::vector<QPushButton*>> boutonsEchiquier;

        void afficherEchiquier();
        void ajouterRoi(int x, int y);
    };
}