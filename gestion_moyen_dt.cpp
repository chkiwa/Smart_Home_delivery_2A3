#include "gestion_moyen_dt.h"
#include "ui_gestion_moyen_dt.h"
#include <QPixmap>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QDate>
#include <QPrinter>
#include <QPrintDialog>
#include <QTextDocument>
gestion_moyen_dt::gestion_moyen_dt(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::gestion_moyen_dt)
{

    ui->setupUi(this);

    animation = new QPropertyAnimation (ui->label_gestion_scooter,"geometry");
    animation->setDuration(20000);
    animation->setStartValue(ui->label_gestion_scooter->geometry());
    animation->setEndValue(QRect(160,10,171,30));
    animation->start();

    ui->listView->setModel(sco.afficherliste());

    QPixmap pix(":/rec/img/logo.png");
    int w = ui->label_pic->width();
    int h = ui->label_pic->height();
    ui->label_pic->setPixmap(pix.scaled(w,h,Qt::KeepAspectRatio));

    int w2 = ui->label_pic_2->width();
    int h2 = ui->label_pic_2->height();
    ui->label_pic_2->setPixmap(pix.scaled(w2,h2,Qt::KeepAspectRatio));

    int w3 = ui->label_pic_3->width();
    int h3 = ui->label_pic_3->height();
    ui->label_pic_3->setPixmap(pix.scaled(w3,h3,Qt::KeepAspectRatio));


    int w4 = ui->label_pic_4->width();
    int h4 = ui->label_pic_4->height();
    ui->label_pic_4->setPixmap(pix.scaled(w4,h4,Qt::KeepAspectRatio));


    ui->listView->setContextMenuPolicy(Qt::CustomContextMenu);
    connect(ui->listView, SIGNAL(customContextMenuRequested(QPoint)), this, SLOT(showContextMenu(QPoint)));


    ui->lineEdit_dispo->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_etat->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_idscooter->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]+")));
    ui->lineEdit_depense->setValidator(new QRegExpValidator(QRegExp("[0-9]{1,3}")));

    ui->lineEdit_dispo_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_etat_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z]+")));
    ui->lineEdit_idscooter_2->setValidator(new QRegExpValidator(QRegExp("[A-Za-z0-9]+")));




    timer = new QTimer(this);
    connect(timer,&QTimer::timeout,this,&::gestion_moyen_dt::fonctionmontre);
    timer->start(1000);

    QDate date=QDate::currentDate();
    QString datetime_text =date.toString();
    ui->label_date->setText(datetime_text);

}

gestion_moyen_dt::~gestion_moyen_dt()
{
    delete ui;
}


void gestion_moyen_dt::on_pushButton_ajoutermdt2_clicked()
{
    QString id=ui->lineEdit_idscooter->text();
    QString etat=ui->lineEdit_etat->text();
    QString dispo=ui->lineEdit_dispo->text();
    float depense=ui->lineEdit_depense->text().toFloat();

    scooter sc(id,etat,dispo,depense);
    bool test1=sc.ajoutscooter();
    if(test1)
    {
    QMessageBox::information(this,"Ajouter un Scooter","Scooter ajouté.\n"
                             "Click cancel to exit.",QMessageBox::Cancel);
    ui->listView->setModel(sco.afficherliste());

    }
    else
        QMessageBox::warning(this,"Ajouter un Livreur","Scooter non ajouté.\n"
                                 "Click cancel to exit.",QMessageBox::Cancel);
    bool test =false;
        if(ui->lineEdit_idscooter->text().isEmpty())
        {ui->lineEdit_idscooter->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_idscooter->setStyleSheet("border: 1px solid blue");
        }

       if(ui->lineEdit_dispo->text().isEmpty())
            {ui->lineEdit_dispo->setStyleSheet("border: 1px solid red");
            test =true;
            }
            else {
            ui->lineEdit_dispo->setStyleSheet("border: 1px solid blue");
            }
       if(ui->lineEdit_etat->text().isEmpty())
            {ui->lineEdit_etat->setStyleSheet("border: 1px solid red");
            test =true;
            }
            else {
            ui->lineEdit_etat->setStyleSheet("border: 1px solid blue");
            }
       if(ui->lineEdit_depense->text().isEmpty())
            {ui->lineEdit_depense->setStyleSheet("border: 1px solid red");
            test =true;
            }
            else {
            ui->lineEdit_depense->setStyleSheet("border: 1px solid blue");
            }

       test=false;
       if((ui->lineEdit_etat->text().isEmpty())||(ui->lineEdit_dispo->text().isEmpty())||(ui->lineEdit_idscooter->text().isEmpty())||(ui->lineEdit_depense->text().isEmpty()))
               {
           test=true;
           QMessageBox::warning(this,"we deliver","Veuillez remplir les champs obligatoires marqués en rouge");
       }
       if(test==false)
  { ui->stackedWidget->setCurrentIndex(0);}
}

void gestion_moyen_dt::showContextMenu(const QPoint &pos)
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


void gestion_moyen_dt::supprimerItem()
{ QMessageBox::StandardButton reply;
    QModelIndex index = ui->listView->currentIndex();
    QString itemtext = index.data(Qt::DisplayRole).toString();

    reply = QMessageBox::question(this,"We Deliver","Voulez vous vraiment supprimer ce Scooter ?",QMessageBox::Cancel|QMessageBox::Ok);
        if(reply == QMessageBox::Ok)

     {
       bool test=sco.supprimer(itemtext);
       if(test)
       {
          ui->listView->setModel(sco.afficherliste());
       }
     }
 }

void gestion_moyen_dt::modifierItem()
{
    QModelIndex index = ui->listView->currentIndex();
    QString itemtext = index.data(Qt::DisplayRole).toString();
    QSqlQuery query;
    query=sco.recuperer(itemtext);
    if(query.exec())
    {
        while(query.next())
        {
            ui->lineEdit_idscooter_2->setText(query.value(0).toString());
            ui->lineEdit_etat_2->setText(query.value(1).toString());
            ui->lineEdit_dispo_2->setText(query.value(2).toString());
            ui->lineEdit_depense_2->setText(query.value(3).toString());

        }
    }
    ui->stackedWidget->setCurrentIndex(2);
}

void gestion_moyen_dt::consulterItem()
{
    QModelIndex index= ui->listView->currentIndex();
    QString itemtext= index.data(Qt::DisplayRole).toString();
    ui->tableView->setModel(sco.afficher(itemtext));

    ui->stackedWidget->setCurrentIndex(3);


ui->stackedWidget->setCurrentIndex(3);
}
void gestion_moyen_dt::on_pushButton_enregistrermdt_clicked()
{

    float depense =ui->lineEdit_depense_2->text().toFloat();
    QString id=ui->lineEdit_idscooter_2->text();
    QString etat=ui->lineEdit_etat_2->text();
    QString dispo=ui->lineEdit_dispo_2->text();

 scooter sc(id,etat,dispo,depense);
 bool test1=sc.modifierscooter();

    if(test1)
    {
        QMessageBox::information(this,"Modifier un scooter","scooter modifié.\n"
                                 "Click cancel to exit.",QMessageBox::Cancel);
        ui->listView->setModel(sc.afficherliste());
        }
        else
            QMessageBox::warning(this,"Modifier un scooter","scooter non modifié.\n"
                                     "Click cancel to exit.",QMessageBox::Cancel);


    bool test =false;
        if(ui->lineEdit_idscooter_2->text().isEmpty())
        {ui->lineEdit_idscooter_2->setStyleSheet("border: 1px solid red");
        test =true;
        }
        else {
        ui->lineEdit_idscooter_2->setStyleSheet("border: 1px solid blue");
        }

       if(ui->lineEdit_dispo_2->text().isEmpty())
            {ui->lineEdit_dispo_2->setStyleSheet("border: 1px solid red");
            test =true;
            }
            else {
            ui->lineEdit_dispo_2->setStyleSheet("border: 1px solid blue");
            }
       if(ui->lineEdit_etat_2->text().isEmpty())
            {ui->lineEdit_etat_2->setStyleSheet("border: 1px solid red");
            test =true;
            }
            else {
            ui->lineEdit_etat_2->setStyleSheet("border: 1px solid blue");
            }
       test=false;
       if((ui->lineEdit_etat_2->text().isEmpty())||(ui->lineEdit_dispo_2->text().isEmpty())||(ui->lineEdit_idscooter_2->text().isEmpty()))
               {
           test=true;
           QMessageBox::warning(this,"we deliver","Veuillez remplir les champs obligatoires marqués en rouge");
       }
       if(test==false)
  { ui->stackedWidget->setCurrentIndex(0);}
}

void gestion_moyen_dt::on_pushButton_ajouterscooter_clicked()
{
    ui->stackedWidget->setCurrentIndex(1);
}

void gestion_moyen_dt::on_pushButton_precedent_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestion_moyen_dt::on_pushButton_precedent_2_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}

void gestion_moyen_dt::on_pushButton_precedent_3_clicked()
{
    ui->stackedWidget->setCurrentIndex(0);
}

void gestion_moyen_dt::on_pushButton_precedent_4_clicked()
{
   ui->stackedWidget->setCurrentIndex(0);
}



void gestion_moyen_dt::on_pushButton_accueil_clicked()
{
    emit homeclicked();
}

void gestion_moyen_dt::on_pushButton_depense_clicked()
{
    ui->stackedWidget->setCurrentIndex(4);
    ui->tableView_2->setModel(sco.afficherdepense());
}

void gestion_moyen_dt::fonctionmontre()
{
    QTime time= QTime::currentTime();
    QString time_text=time.toString("hh:mm:ss");
    ui->label_time->setText(time_text);
}


void gestion_moyen_dt::on_pushButton_print_clicked()
{
    QString strStream;
    QTextStream out(&strStream);



    const int rowCount = ui->tableView_2->model()->rowCount();
    const int columnCount = ui->tableView_2->model()->columnCount();

    out <<  "<html>\n"
        "<head>\n"

        "<meta Content=\"Text/html; charset=Windows-1251\">\n"
        <<  QString("<title>%60 les depenses</title>\n").arg(ui->label_21->text())
        <<  "</head>\n"
        "<body bgcolor=#ffffff link=#5000A0>\n"
        "<table border=1 cellspacing=0 cellpadding=2>\n";
    out << "<thead><tr bgcolor=#f0f0f0>";
    for (int column = 0; column < columnCount; column++)
        if (! ui->tableView_2->isColumnHidden(column))
            out << QString("<th>%1</th>").arg(ui->tableView_2->model()->headerData(column, Qt::Horizontal).toString());
    out << "</tr></thead>\n";

    for (int row = 0; row < rowCount; row++) {
        out << "<tr>";
        for (int column = 0; column < columnCount; column++) {
            if (!ui->tableView_2->isColumnHidden(column)) {
                QString data = ui->tableView_2->model()->data(ui->tableView_2->model()->index(row, column)).toString().simplified();
                out << QString("<td bkcolor=0>%1</td>").arg((!data.isEmpty()) ? data : QString("&nbsp;"));
            }
        }
        out << "</tr>\n";
    }
    out <<  "</table>\n"
        "</body>\n"
        "</html>\n";

    QTextDocument *document = new QTextDocument();
    document->setHtml(strStream);

    QPrinter printer;

    QPrintDialog *dialog = new QPrintDialog(&printer, NULL);
    if (dialog->exec() == QDialog::Accepted) {
        document->print(&printer);
    }

    delete document;
}

void gestion_moyen_dt::on_pushButton_chercher_clicked()
{
    QString id=ui->lineEdit_chercher->text();
       if(sco.recherche(id))
       {
           ui->tableView->setModel(sco.afficher(id));
           ui->stackedWidget->setCurrentIndex(3);
       }
       else
       {
           QMessageBox::critical(nullptr, QObject::tr("Error"),
                                 QObject::tr("scooter n'est pas trouvé.\n"
                                             "Click Cancel to exit."), QMessageBox::Cancel);
       }
}

void gestion_moyen_dt::on_lineEdit_chercher_textChanged(const QString &arg1)
{
    QString id =arg1;
       ui->listView->setModel(sco.recherche(id));
       if(ui->lineEdit_chercher->text()=="")
       {
        ui->listView->setModel(sco.afficherliste());
       }
}
