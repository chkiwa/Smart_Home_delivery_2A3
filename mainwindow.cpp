#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QPixmap pix(":/rec/img/logo.png");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));




    int w3 = ui->label_pic_3->width();
    int h3 = ui->label_pic_3->height();
    ui->label_pic_3->setPixmap(pix.scaled(w3,h3,Qt::KeepAspectRatio));


    ui->stackedWidget->insertWidget(4,&emp);
    ui->stackedWidget->insertWidget(5,&moy);

    connect(&emp,SIGNAL(homeclicked()),this,SLOT(movehome()));
    connect(&moy,SIGNAL(homeclicked()),this,SLOT(movehome()));
}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_seconnecter_clicked()
{ bool test=false;

    if(ui->lineEdit_ID->text().isEmpty())
    {ui->lineEdit_ID->setStyleSheet("border: 1px solid red");

    }
    else {
    ui->lineEdit_ID->setStyleSheet("border: 1px solid blue");
    }

    if(ui->lineEdit_mdp->text().isEmpty())
    {ui->lineEdit_mdp->setStyleSheet("border: 1px solid red");

    }
    else {
    ui->lineEdit_mdp->setStyleSheet("border: 1px solid blue");
    }

    if(ui->lineEdit_ID->text().isEmpty()||ui->lineEdit_mdp->text().isEmpty())
    { test=true;
       QMessageBox::warning(this,"we deliver","Veuillez remplir les champs obligatoires marqués en rouge");
    }
    if(test==false)
    {QString id=ui->lineEdit_ID->text();
    QString mdp=ui->lineEdit_mdp->text();
if(id=="admin20" && mdp=="admin")
    ui->stackedWidget->setCurrentIndex(1);
else
   { QMessageBox::warning(this,"we deliver","Veuillez vérifier votre mot de passe ou votre identifiant");}
    }
}

void MainWindow::on_pushButton_deconnecter_clicked()
{
 ui->stackedWidget->setCurrentIndex(0);
}

void MainWindow::on_pushButton_employes_clicked()
{
    ui->stackedWidget->setCurrentIndex(2);
}

void MainWindow::movehome()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void MainWindow::on_pushButton_mdt_clicked()
{
    ui->stackedWidget->setCurrentIndex(3);
}

void MainWindow::on_pushButton_music_clicked()
{
    m = new music(this);
    m->show();
}
