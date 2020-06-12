#include "towerchoice.h"
#include "ui_towerchoice.h"
int  towernum;
towerchoice::towerchoice(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::towerchoice)
{
    ui->setupUi(this);
}

towerchoice::~towerchoice()
{
    delete ui;
}


void towerchoice::on_commandLinkButton_3_clicked()
{
  towernum=1;
}
