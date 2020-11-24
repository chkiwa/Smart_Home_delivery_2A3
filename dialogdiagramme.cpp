#include "dialogdiagramme.h"
#include "ui_dialogdiagramme.h"

Dialogdiagramme::Dialogdiagramme(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialogdiagramme)
{
    ui->setupUi(this);
    ui->plot->addGraph(0)->setScatterStyle(QCPScatterStyle::ssCircle);
    ui->plot->addGraph(0)->setLineStyle(QCPGraph::lsNone);



Dialogdiagramme::~Dialogdiagramme()
{
    delete ui;
}

 void Dialogdiagramme::on_add_clicked()
{
}

void Dialogdiagramme::on_clear_click
