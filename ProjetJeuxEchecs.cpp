#include "ProjetJeuxEchecs.h"

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget* parent)
    : QMainWindow(parent)
    , ui(new Ui::ProjetJeuxEchecsClass())
{
    ui->setupUi(this);

    for (int row = 0; row < 8; ++row) {
        for (int col = 0; col < 8; ++col) {
            QPushButton* button = new QPushButton(this);
            button->setMinimumSize(80, 80);
            button->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);


            QString color = (row + col) % 2 == 0 ? "#f0d9b5" : "#b58863"; // couleurs classiques échiquier
            button->setStyleSheet(QString("background-color: %1;").arg(color));


            ui->gridLayout->addWidget(button, row, col);
        }
    }
}

ProjetJeuxEchecs::~ProjetJeuxEchecs()
{
    delete ui;
};
