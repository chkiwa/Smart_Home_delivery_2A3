#include "scooter.h"

scooter::scooter()
{
id="";
etat="";
dispo="";
depense=0;
}

scooter::scooter(QString id,QString etat,QString dispo,float depense)
{
    this->id=id;
    this->etat=etat;
    this->dispo=dispo;
    this->depense=depense;
}

bool scooter::ajoutscooter()
{  QSqlQuery query;

    QString res1 = QString::number(depense);
    query.prepare("INSERT INTO scooter2 (id, etat, dispo,depense)VALUES(:id,:etat ,:dispo, :depense)");
    query.bindValue(":id",id);
    query.bindValue(":etat",etat);
    query.bindValue(":dispo",dispo);
    query.bindValue(":depense",res1);
    return query.exec();
}

QSqlQuery scooter::load_data()
{
    QSqlQuery query;
    query.prepare("select id from scooter2");
    return query;
}

QSqlQueryModel* scooter::afficher(QString itemtext)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from scooter2 where id='"+itemtext+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("Etat"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("Disponibilité"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("Depense"));
       return model;

}

bool scooter::supprimer(QString itemtext)
{
       QSqlQuery query;
       query.prepare("Delete from scooter2 where id='"+itemtext+"'");
        return query.exec();

}

QSqlQueryModel* scooter::afficherliste()
{
    QSqlQueryModel *modal=new QSqlQueryModel();
        QSqlQuery query=load_data();
        query.exec();
        modal->setQuery(query);
        return modal;
}

QSqlQueryModel* scooter::afficherdepense()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from scooter2 ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(1,Qt::Horizontal,QObject::tr("Etat"));
    model->setHeaderData(2,Qt::Horizontal,QObject::tr("Disponibilité"));
    model->setHeaderData(3,Qt::Horizontal,QObject::tr("Depense"));
    return model;
}

bool scooter::modifierscooter()
{
        QSqlQuery query;

        QString res1 = QString::number(depense);
        query.prepare("update scooter2 set id='"+id+"', etat='"+etat+"', dispo='"+dispo+"',depense='"+res1+"' where id='"+id+"' " );
        query.bindValue(":id",id);
        query.bindValue(":etat",etat);
        query.bindValue(":dispo",dispo);
        query.bindValue(":depense",res1);
        return query.exec();
}

QSqlQuery scooter::recuperer(QString itemtext)
{
    QSqlQuery query;
        query.prepare("select * from scooter2 where id='"+itemtext+"'");
        query.exec();
        return query;
}
