#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <gestion_employes.h>
#include <gestion_moyen_dt.h>
#include "music.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:

    void on_pushButton_seconnecter_clicked();

    void on_pushButton_deconnecter_clicked();

    void on_pushButton_employes_clicked();

    void movehome();

    void on_pushButton_mdt_clicked();

    void on_pushButton_music_clicked();

private:
    Ui::MainWindow *ui;
    Gestion_employes emp;
    gestion_moyen_dt moy;
    music *m;
};
#endif // MAINWINDOW_H
