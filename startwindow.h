#ifndef STARTWINDOW_H
#define STARTWINDOW_H

#include <QDialog>
#include "mainwindow.h"


namespace Ui {
class startwindow;
}

class startwindow : public QDialog
{
    Q_OBJECT

public:
    explicit startwindow(QWidget *parent = 0);
    ~startwindow();


private slots:
    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

private:
    Ui::startwindow *ui;
    MainWindow main;


};

#endif // STARTWINDOW_H
