#ifndef EMPLOYES_ATTRIBUT_H
#define EMPLOYES_ATTRIBUT_H
#include <QString>

class employes_attribut
{ QString nom;
  QString prenom;
  QString id;
  QString num_tele;

public:
    employes_attribut();
    employes_attribut(QString ,QString ,QString , QString);
    QString get_nom(){return nom;}
    QString get_prenom(){return prenom;}
    QString get_id(){return id;}
    QString get_num(){return num_tele ;}


};

#endif // EMPLOYES_ATTRIBUT_H
