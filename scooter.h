#ifndef SCOOTER_H
#define SCOOTER_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>


class scooter
{ QString id,etat,dispo;
    float depense;
public:
    scooter();
    scooter(QString,QString,QString,float);
    QString get_id(){return id;}
    QString get_etat(){return etat;}
    QString get_dispo(){return dispo;}
    float get_depense(){return depense;}

    bool ajoutscooter();
    bool modifierscooter( );
    QSqlQueryModel* afficher(QString );
    QSqlQueryModel* afficherdepense();
    QSqlQuery load_data();
    QSqlQueryModel* afficherliste();
    bool supprimer(QString);
    QSqlQuery recuperer(QString);
    bool recherche(QString id);
};

#endif // SCOOTER_H
