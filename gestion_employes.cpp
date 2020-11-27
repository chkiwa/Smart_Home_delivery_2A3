#include "gestion_employes.h"
#include "ui_gestion_employes.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include "attemploye.h"
#include <QSqlRecord>
#include <QSortFilterProxyModel>
#include <QtCharts>
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
#include <QtCharts/QLegend>

Gestion_employes::Gestion_employes(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Gestion_employes)
{
    ui->setupUi(this);

    animation = new QPropertyAnimation (ui->label_gestion_livreur,"geometry");
    animation->setDuration(10000);
    animation->setStartValue(ui->label_gestion_livreur->geometry());
    animation->setEndValue(QRect(160,10,171,30));
    animation->start();

    ui->listView->setModel(temp.afficherliste());

    QPixmap pix(":/rec/img/logo.png");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    int w1 = ui->label_pic_1->width();
    int h1 = ui->label_pic_1->height();
    ui->label_pic_1->setPixmap(pix.scaled(w1,h1,Qt::KeepAspectRatio));

    int w2 = ui->label_pic_2->width();
    int h2 = ui->label_pic_2->height();
    ui->label_pic_2->setPixmap(pix.scaled(w2,h2,Qt::KeepAspectRatio));

    int w3 = ui->label_pic_3->width();
    int h3 = ui->label_pic_3->height();
    ui->label_pic_3->setPixmap(pix.scaled(w3,h3,Qt::KeepAspectRatio));


    ui->lineEdit_nom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_prenom->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_id->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]+")));
    ui->lineEdit_numero_tele->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->lineEdit_mdp->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]+")));
    ui->lineEdit_heure->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));
    ui->lineEdit_presence->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_idscooter->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]+")));


    ui->lineEdit_nom_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_prenom_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_id_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]+")));
    ui->lineEdit_numero_tele_2->setValidator(new QRegExpValidator(QRegExp("[0-9]{8}")));





        ui->listView->setContextMenuPolicy(Qt::CustomContextMenu); //menu de bouton droite
        connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));





}

Gestion_employes::~Gestion_employes()
{
    delete ui;
}

void Gestion_employes::on_pushButton_ajouter1_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void Gestion_employes::showContextMenu(const QPoint &pos)
{
    // Handle global position
        QPoint globalPos = ui->listView->mapToGlobal(pos);

        // Create menu and insert some actions
        QMenu myMenu;
        myMenu.addAction("consulter", this, SLOT(consulterItem()));
        myMenu.addAction("modifier",  this, SLOT(modifierItem()));
        myMenu.addAction("supprimer", this, SLOT(supprimerItem()));

        // Show context menu at handling position
        myMenu.exec(globalPos);
}

void Gestion_employes::supprimerItem()
{QMessageBox::StandardButton reply;
    QModelIndex index = ui->listView->currentIndex();
            QString itemtext = index.data(Qt::DisplayRole).toString();

    reply = QMessageBox::question(this,"We Deliver","Voulez vous vraiment supprimer ce Livreur ?",QMessageBox::Cancel|QMessageBox::Ok);
        if(reply == QMessageBox::Ok)

          {

       bool test=temp.supprimer(itemtext);
       if(test)
       {
          ui->listView->setModel(temp.afficherliste());
       }
           }
}


void Gestion_employes::modifierItem()
{  QModelIndex index = ui->listView->currentIndex();
    QString itemtext = index.data(Qt::DisplayRole).toString();
    QSqlQuery query;
    query=temp.recuperer(itemtext);
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_id_2->setText(query.value(0).toString());
            ui->lineEdit_nom_2->setText(query.value(1).toString());
            ui->lineEdit_prenom_2->setText(query.value(2).toString());
            ui->lineEdit_numero_tele_2->setText(query.value(3).toString());
            ui->lineEdit_mdp_2->setText(query.value(4).toString());
            ui->lineEdit_presence_2->setText(query.value(5).toString());
            ui->lineEdit_heure_2->setText(query.value(6).toString());
            ui->lineEdit_idscooter_2->setText(query.value(7).toString());
        }
    }
ui->stackedWidget->setCurrentIndex(2);
}
void Gestion_employes::consulterItem()
{  QModelIndex index= ui->listView->currentIndex();
   QString itemtext= index.data(Qt::DisplayRole).toString();
   ui->tableView->setModel(temp.afficher(itemtext));
   ui->stackedWidget->setCurrentIndex(3);
}

void Gestion_employes::on_pushButton_ajouter2_clicked()
{
    long num_tele =ui->lineEdit_numero_tele->text().toLong();
    QString nom=ui->lineEdit_nom->text();
    QString prenom=ui->lineEdit_prenom->text();
    QString id=ui->lineEdit_id->text();
    QString mdp=ui->lineEdit_mdp->text();
    QString presence=ui->lineEdit_presence->text();
    QString idsco=ui->lineEdit_idscooter->text();
    int heure_m =ui->lineEdit_heure->text().toInt();

 attemploye emp(nom,prenom,id,num_tele,mdp,presence,idsco,heure_m);
 bool test1=emp.ajouteremploye();
 if(test1)
 {
 QMessageBox::information(this,"Ajouter un Livreur","Livreur ajouté.\n"
                          "Click cancel to exit.",QMessageBox::Cancel);
  ui->listView->setModel(emp.afficherliste());
 }
 else
     QMessageBox::warning(this,"Ajouter un Livreur","Livreur non ajouté.\n"
                              "Click cancel to exit.",QMessageBox::Cancel);


    bool test =false;

        if(ui->lineEdit_id->text().isEmpty())
        {ui->lineEdit_id->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_id->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_nom->text().isEmpty())
        {ui->lineEdit_nom->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_nom->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_prenom->text().isEmpty())
        {ui->lineEdit_prenom->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_prenom->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_numero_tele->text().isEmpty())
        {ui->lineEdit_numero_tele->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_numero_tele->setStyleSheet("border: 1px solid blue");
        }
        if(ui->lineEdit_mdp->text().isEmpty())
        {ui->lineEdit_mdp->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_mdp->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_idscooter->text().isEmpty())
        {ui->lineEdit_idscooter->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_idscooter->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_presence->text().isEmpty())
        {ui->lineEdit_presence->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_presence->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_heure->text().isEmpty())
        {ui->lineEdit_heure->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_heure->setStyleSheet("border: 1px solid blue");
        }


        test=false;
        if((ui->lineEdit_id->text().isEmpty())||(ui->lineEdit_prenom->text().isEmpty())||(ui->lineEdit_nom->text().isEmpty())||(ui->lineEdit_numero_tele->text().isEmpty())||(ui->lineEdit_mdp->text().isEmpty())||(ui->lineEdit_idscooter->text().isEmpty())||(ui->lineEdit_presence->text().isEmpty())||(ui->lineEdit_heure->text().isEmpty()))
                {
            test=true;
            QMessageBox::warning(this,"we deliver","Veuillez remplir les champs obligatoires marqués en rouge");
        }
        if(test==false)
   { ui->stackedWidget->setCurrentIndex(0);}
}



void Gestion_employes::on_pushButton_enregistrer_clicked()
{

    long num_tele =ui->lineEdit_numero_tele_2->text().toLong();
    QString nom=ui->lineEdit_nom_2->text();
    QString prenom=ui->lineEdit_prenom_2->text();
    QString id=ui->lineEdit_id_2->text();
    QString mdp=ui->lineEdit_mdp_2->text();
    QString presence=ui->lineEdit_presence_2->text();
    QString idsco=ui->lineEdit_idscooter_2->text();
    int heure_m =ui->lineEdit_heure_2->text().toInt();

 attemploye emp(nom,prenom,id,num_tele,mdp,presence,idsco,heure_m);
 bool test1=emp.modifieremploye();

    if(test1)
    {
        QMessageBox::information(this,"Modifier un Livreur","Livreur modifié.\n"
                                 "Click cancel to exit.",QMessageBox::Cancel);
        ui->listView->setModel(temp.afficherliste());
        }
        else
            QMessageBox::warning(this,"Modifier un Livreur","Livreur non modifié.\n"
                                     "Click cancel to exit.",QMessageBox::Cancel);



    bool test =false;
        if(ui->lineEdit_id_2->text().isEmpty())
        {ui->lineEdit_id_2->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_id_2->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_nom_2->text().isEmpty())
        {ui->lineEdit_nom_2->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_nom_2->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_prenom_2->text().isEmpty())
        {ui->lineEdit_prenom_2->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_prenom_2->setStyleSheet("border: 1px solid blue");
        }

        if(ui->lineEdit_numero_tele_2->text().isEmpty())
        {ui->lineEdit_numero_tele_2->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_numero_tele_2->setStyleSheet("border: 1px solid blue");
        }
        test=false;
        if((ui->lineEdit_id_2->text().isEmpty())||(ui->lineEdit_prenom_2->text().isEmpty())||(ui->lineEdit_nom_2->text().isEmpty())||(ui->lineEdit_numero_tele_2->text().isEmpty()))
                {
            test=true;
            QMessageBox::warning(this,"we deliver","Veuillez remplir les champs obligatoires marqués en rouge");
        }
        if(test==false)
   { ui->stackedWidget->setCurrentIndex(0);}
}

void Gestion_employes::on_pushButton_Accueil_clicked()
{
    emit homeclicked();
}

void Gestion_employes::on_pushButton_return_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Gestion_employes::on_pushButton_return_2_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Gestion_employes::on_pushButton_return_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}


void Gestion_employes::on_pushButton_return_4_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void Gestion_employes::on_pushButton_presence_clicked()
{   ui->tableView_2->setModel(temp.afficherendement());
    ui->stackedWidget->setCurrentIndex(4);
}



void Gestion_employes::on_pushButton_trier_clicked()
{

QSqlQueryModel * myModel=new QSqlQueryModel(ui->tableView_2);
   QSqlQuery query;
   if(query.exec("select * from livreur1"))
   {myModel->setQuery(query);
      QSortFilterProxyModel *proxyModel = new QSortFilterProxyModel(myModel);
      proxyModel->setSourceModel(myModel);
      ui->tableView_2->setModel(myModel);
      ui->tableView_2->setSortingEnabled(true);
      ui->tableView_2->setModel(proxyModel);

   }


}

void Gestion_employes::on_pushButton_diagramme_clicked()
{
    QPieSeries *series = new QPieSeries();
        QSqlQuery query;
                query=temp.stat();
        while(query.next())
        {
            series->append(query.value(0).toString(),query.value(6).toInt());
        }

        QChart * chart=new  QChart();
        chart->addSeries(series);
        chart->setTitle("le rendement des livreurs");

        QChartView * chartView=new QChartView(chart);
        chartView ->setParent(ui->horizontalFrame);
        chartView->setFixedSize(ui->horizontalFrame->size());
        ui->stackedWidget->setCurrentIndex(5);


}




void Gestion_employes::on_pushButton_precedent_clicked()
{
 ui->stackedWidget->setCurrentIndex(4);
}
