 #include "attemploye.h"


attemploye::attemploye()
{
nom ="";
prenom ="";
id ="";
numero_tele =0;
mdp="";
presence="";
idsco="";
heure_m=0;

}

attemploye::attemploye(QString nom,QString prenom,QString id,long numero_tele,QString mdp,QString presence,QString idsco,int heure_m)
{
    this->nom=nom;
    this->prenom=prenom;
    this->id=id;
    this->numero_tele=numero_tele;
    this->mdp=mdp;
    this->presence=presence;
    this->idsco=idsco;
    this->heure_m=heure_m;
}

bool attemploye::ajouteremploye()
{  QSqlQuery query;
   QString res1 = QString::number(numero_tele);
   QString res2 = QString::number(heure_m);
   query.prepare("INSERT INTO LIVREUR1 (id, nom, prenom, numero_tele, mdp, presence, idsco, heure_m)VALUES(:id,:nom ,:prenom, :numero_tele, :mdp, :presence, :idsco, :heure_m)");
   query.bindValue(":id",id);
   query.bindValue(":nom",nom);
   query.bindValue(":prenom",prenom);
   query.bindValue(":mdp",mdp);
   query.bindValue(":numero_tele",res1);
   query.bindValue(":presence",presence);
   query.bindValue(":idsco",idsco);
   query.bindValue(":heure_m",res2);

   return query.exec();
}

bool attemploye::modifieremploye()
{
    QSqlQuery query;
       QString res1 = QString::number(numero_tele);
       QString res2 = QString::number(heure_m);
    query.prepare("update livreur1 set id='"+id+"' ,nom='"+nom+"' ,prenom='"+prenom+"' ,numero_tele='"+res1+"', mdp='"+mdp+"', presence='"+presence+"', idsco='"+idsco+"', heure_m='"+res2+"' where id='"+id+"' " );
    query.bindValue(":id",id);
    query.bindValue(":nom",nom);
    query.bindValue(":prenom",prenom);
    query.bindValue(":mdp",mdp);
    query.bindValue(":numero_tele",res1);
    query.bindValue(":presence",presence);
    query.bindValue(":idsco",idsco);
    query.bindValue(":heure_m",res2);

     return query.exec();
}

QSqlQuery attemploye::load_data()
{
    QSqlQuery query;
    query.prepare("select id from livreur1");
    return query;
}

QSqlQueryModel* attemploye::afficher(QString itemtext)
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from livreur1 where id='"+itemtext+"' ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
       model->setHeaderData(1,Qt::Horizontal,QObject::tr("NOM"));
       model->setHeaderData(2,Qt::Horizontal,QObject::tr("Prenom"));
       model->setHeaderData(3,Qt::Horizontal,QObject::tr("Numero téléphone"));
       model->setHeaderData(4,Qt::Horizontal,QObject::tr("Mot de passe"));
       model->setHeaderData(5,Qt::Horizontal,QObject::tr("Présence"));
       model->setHeaderData(7,Qt::Horizontal,QObject::tr("IDscooter"));
       model->setHeaderData(6,Qt::Horizontal,QObject::tr("Heure(m)"));
       return model;
}
bool attemploye::supprimer(QString itemtext)
{
       QSqlQuery query;
       query.prepare("Delete from livreur1 where id='"+itemtext+"'");
        return query.exec();

}

 QSqlQueryModel* attemploye::afficherliste()
 {
     QSqlQueryModel *modal=new QSqlQueryModel();
         QSqlQuery query=load_data();
         query.exec();
         modal->setQuery(query);
         return modal;
 }

QSqlQuery attemploye::recuperer(QString itemtext)
{
    QSqlQuery query;
        query.prepare("select * from livreur1 where id='"+itemtext+"'");
        query.exec();
        return query;
}


QSqlQueryModel* attemploye::afficherendement()
{
    QSqlQueryModel* model=new QSqlQueryModel();
    model->setQuery("select * from livreur1 ");
    model->setHeaderData(0,Qt::Horizontal,QObject::tr("ID"));
    model->setHeaderData(5,Qt::Horizontal,QObject::tr("Présence"));
    model->setHeaderData(6,Qt::Horizontal,QObject::tr("Heure(m)"));
    return model;
}

QSqlQuery attemploye::stat()
{
    QSqlQuery query;
        query.prepare("select *from livreur1 ");
        query.exec();
        return query;
}

QSqlQueryModel* attemploye::recherche(QString id)
 {
     QSqlQueryModel *model=new QSqlQueryModel();
     QSqlQuery query;
     query.prepare("select id from livreur1 where id='"+id+"'");
     query.exec();
     model->setQuery(query);
     return model;
 }

