#include "endwindow.h"
#include "ui_endwindow.h"
#include "mainwindow.h"
#include<QPushButton>
Endwindow::Endwindow(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Endwindow)
{
    ui->setupUi(this);
    QPushButton *btn1 =new QPushButton;
    QPushButton *btn2 =new QPushButton;
    btn1->setParent(this);
    btn2->setParent(this);
    btn1->setText("重新开始");
    btn2->setText("退出游戏");
    btn1->resize(100,50);
    btn1->move(150,300);
    btn2->resize(100,50);
    btn1->move(400,300);
    this->setFixedSize(1000,800);
    connect(btn1,&QPushButton::clicked,this,&Endwindow::restart);
    connect(btn2,&QPushButton::clicked,this,&Endwindow::close);
}

Endwindow::~Endwindow()
{
    delete ui;
}

void Endwindow::restart(){this->close();w->close();w->show();}
