#include "suppression.h"
#include "ui_suppression.h"

suppression::suppression(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::suppression)
{
    ui->setupUi(this);
}

suppression::~suppression()
{
    delete ui;
}
