#ifndef ATTEMPLOYE_H
#define ATTEMPLOYE_H
#include <QString>
#include <QSqlQuery>
#include <QSqlQueryModel>

class attemploye
{QString nom,prenom,id,mdp,presence,idsco;
    int heure_m;
    long numero_tele;
public:
    attemploye();
    attemploye(QString ,QString,QString,long,QString,QString,QString,int);

    QString get_nom(){return nom;}
    QString get_prenom(){return prenom;}
    QString get_id(){return id;}
    long get_num_tele(){return numero_tele;}
    QString get_mdp(){return mdp;}
    QString get_presence(){return presence;}
    QString get_idso(){return idsco;}
    int get_heure_m(){return heure_m;}

    void setnom(QString nom){this->nom=nom;}
    void setprenom(QString prenom){this->prenom=prenom;}
    void setid(QString id){this->id=id;}
    void setnum_tel(int numero_tele){this->numero_tele=numero_tele;}
    void setmdp(QString mdp){this->mdp=mdp;}
    void setpresence(QString presence){this->presence=presence;}
    void set_idsco(QString idsco){this->idsco=idsco;}
    void setheure(int heure_m){this->heure_m=heure_m;}

    bool ajouteremploye();
    bool modifieremploye( );
    QSqlQueryModel* afficher(QString );
   // QSqlQueryModel* recherche(QString );
    QSqlQuery load_data();
    QSqlQueryModel* afficherendement();
    QSqlQueryModel* afficherliste();
    bool supprimer(QString);
    QSqlQuery recuperer(QString);
    QSqlQuery stat();

};

#endif // ATTEMPLOYE_H
