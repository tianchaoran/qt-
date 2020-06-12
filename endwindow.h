#ifndef ENDWINDOW_H
#define ENDWINDOW_H

#include <QDialog>
#include "mainwindow.h"
namespace Ui {
class Endwindow;
}

class Endwindow : public QDialog
{
    Q_OBJECT

public:
    explicit Endwindow(QWidget *parent = 0);
    ~Endwindow();
    MainWindow* w;
    void restart();


private:
    Ui::Endwindow *ui;
};

#endif // ENDWINDOW_H
