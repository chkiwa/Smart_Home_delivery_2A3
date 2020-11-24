#ifndef DIALOGDIAGRAMME_H
#define DIALOGDIAGRAMME_H

#include <QDialog>

namespace Ui {
class Dialogdiagramme;
}

class Dialogdiagramme : public QDialog
{
    Q_OBJECT

public:
    explicit Dialogdiagramme(QWidget *parent = nullptr);
    ~Dialogdiagramme();

    void addpoint(double x,double y);
    void cleardata();
    void plot();



private slots:
    void on_add_clicked();

    void on_clear_clicked();

private:
    Ui::Dialogdiagramme *ui;

    QVector<double> qv_x, qv_y;
};

#endif // DIALOGDIAGRAMME_H
