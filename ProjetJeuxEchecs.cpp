#include "ProjetJeuxEchecs.h"

ProjetJeuxEchecs::ProjetJeuxEchecs(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::ProjetJeuxEchecsClass())
{
    ui->setupUi(this);
}

ProjetJeuxEchecs::~ProjetJeuxEchecs()
{
    delete ui;
}
