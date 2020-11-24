#include "employes_attribut.h"

employes_attribut::employes_attribut()
{
nom="";
prenom="";
id="";
num_tele="";
}

employes_attribut::employes_attribut(QString nom, QString prenom, QString id, QString num_tele)
{
    this->nom=nom;
    this->prenom=prenom;
    this->id=id;
    this->num_tele=num_tele;
}
