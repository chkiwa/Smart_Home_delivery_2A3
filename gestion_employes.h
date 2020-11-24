#ifndef GESTION_EMPLOYES_H
#define GESTION_EMPLOYES_H
#include <QListView>
#include <QMenu>
#include <QWidget>
#include "attemploye.h"
#include <QPropertyAnimation>

namespace Ui {
class Gestion_employes;
}

class Gestion_employes : public QWidget
{
    Q_OBJECT

public:
    explicit Gestion_employes(QWidget *parent = nullptr);
    ~Gestion_employes();

private slots:
    void on_pushButton_ajouter1_clicked();

    void on_pushButton_ajouter2_clicked();
    void showContextMenu(const QPoint&);
    void supprimerItem();
    void modifierItem();
    void consulterItem();


    void on_pushButton_enregistrer_clicked();

    void on_pushButton_Accueil_clicked();

    void on_pushButton_return_clicked();

    void on_pushButton_return_2_clicked();

    void on_pushButton_return_3_clicked();

    void on_pushButton_return_4_clicked();

    void on_pushButton_presence_clicked();

    void on_pushButton_trier_clicked();

    void on_pushButton_diagramme_clicked();




    void on_pushButton_precedent_clicked();

private:
    QPropertyAnimation *animation;
    Ui::Gestion_employes *ui;
    attemploye temp;

    QVector<double> qv_x, qv_y;

signals:
    void homeclicked();

};

#endif // GESTION_EMPLOYES_H
