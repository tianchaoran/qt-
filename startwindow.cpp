#include "startwindow.h"
#include "ui_startwindow.h"
#include<QPushButton>
#include"mainwindow.h"
#include"ui_mainwindow.h"

startwindow::startwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::startwindow)
{
    ui->setupUi(this);
    this->setFixedSize(1820,960);
    this->setWindowTitle("the war of pixel");
}

startwindow::~startwindow()
{
    delete ui;
}

void startwindow::on_pushButton_clicked()
{
    this->close();
    main.setCheckPoint(1);
    main.show();
}

void startwindow::on_pushButton_2_clicked()
{
    this->close();
    main.setCheckPoint(2);
    main.show();
}
