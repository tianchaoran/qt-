#ifndef TOWERCHOICE_H
#define TOWERCHOICE_H

#include <QWidget>

namespace Ui {
class towerchoice;
}

class towerchoice : public QWidget
{
    Q_OBJECT

public:
    explicit towerchoice(QWidget *parent = 0);
    ~towerchoice();
    int towernum;
private slots:


    void on_commandLinkButton_3_clicked();

private:
    Ui::towerchoice *ui;
};

#endif // TOWERCHOICE_H
