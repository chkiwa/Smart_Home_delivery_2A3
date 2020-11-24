#include "mainwindow.h"
#include <QMessageBox>
#include "connection.h"
#include <QApplication>
#include <QtDebug>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    connection c;

    if(c.createconnect())
    { MainWindow w;
        w.show();
        qDebug()<<"connexion etabli !";
        return a.exec();
    }
    else
        qDebug()<<"probleme de connection !";
    return a.exec();

}
