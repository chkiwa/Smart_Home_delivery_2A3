#ifndef GESTION_MOYEN_DT_H
#define GESTION_MOYEN_DT_H
#include <QMenu>
#include <QWidget>
#include <QTimer>
#include "scooter.h"
#include <QPropertyAnimation>
#include <QPlainTextEdit>
namespace Ui {
class gestion_moyen_dt;
}

class gestion_moyen_dt : public QWidget
{
    Q_OBJECT

public:
    explicit gestion_moyen_dt(QWidget *parent = nullptr);
    ~gestion_moyen_dt();

private slots:
    void on_pushButton_ajoutermdt2_clicked();
    void showContextMenu(const QPoint&);
    void supprimerItem();
    void modifierItem();
    void consulterItem();

    void on_pushButton_enregistrermdt_clicked();

    void on_pushButton_ajouterscooter_clicked();

    void on_pushButton_precedent_clicked();

    void on_pushButton_precedent_2_clicked();

    void on_pushButton_precedent_3_clicked();

    void on_pushButton_precedent_4_clicked();

    void on_pushButton_accueil_clicked();

    void on_pushButton_depense_clicked();


    void on_pushButton_print_clicked();

    void on_pushButton_chercher_clicked();

public slots:
     void fonctionmontre();


private:
    QPropertyAnimation *animation;
    Ui::gestion_moyen_dt *ui;
    QTimer *timer;

    scooter sco;


signals:
    void homeclicked();
};

#endif // GESTION_MOYEN_DT_H
