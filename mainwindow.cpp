﻿#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "waypoint.h"
#include "enemy.h"
#include "bullet.h"
#include "plistreader.h"
#include <QPainter>
#include <QMouseEvent>
#include <QtGlobal>
#include <QMessageBox>
#include <QTimer>
#include <QXmlStreamReader>
#include "endwindow.h"
#include <enemy1.h>
static const int TowerCost = 300;
extern int towernum;
class Endwindow;
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , m_waves(3)
    , m_playerHp(5)
    , m_playrGold(1000)
    , m_gameEnded(false)
    , m_gameWin(false)
{
    ui->setupUi(this);



    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(updateMap()));

}

MainWindow::~MainWindow()
{
    delete ui;
    delete timer;
}

void MainWindow::loadTowerPositions()
{
    PListReader reader;
    if(checkPoint == 1){
        QFile file(":/config/TowersPosition.plist");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
            return;
        }
        reader.read(&file);
        QList<QVariant> array = reader.data();
        foreach (QVariant dict, array)
        {
            QMap<QString, QVariant> point = dict.toMap();
            int x = point.value("x").toInt();
            int y = point.value("y").toInt();
            m_towerPositionsList.push_back(QPoint(x, y));
        }
        file.close();
    }else{
        QFile file(":/config/TowersPosition1.plist");
        if (!file.open(QFile::ReadOnly | QFile::Text))
        {
            QMessageBox::warning(this, "TowerDefense", "Cannot Open TowersPosition.plist");
            return;
        }
        reader.read(&file);
        QList<QVariant> array = reader.data();
        foreach (QVariant dict, array)
        {
            QMap<QString, QVariant> point = dict.toMap();
            int x = point.value("x").toInt();
            int y = point.value("y").toInt();
            m_towerPositionsList.push_back(QPoint(x, y));
        }
        file.close();
    }
}

void MainWindow::paintEvent(QPaintEvent *)
{
    if (m_gameEnded || m_gameWin)
    {
        ew=new Endwindow;
        ew->show();
        m_gameEnded=0;
        QString text = m_gameEnded ? "YOU LOST!!!" : "YOU WIN!!!";
        QPainter painter(this);
        painter.setPen(QPen(Qt::red));
        painter.drawText(rect(), Qt::AlignCenter, text);
        return;
    }

    QPixmap cachePix(":/image/Bg.png");
    QPainter cachePainter(&cachePix);

    foreach (const TowerPosition &towerPos, m_towerPositionsList)
        towerPos.draw(&cachePainter);

    foreach (const Tower *tower, m_towersList)
        tower->draw(&cachePainter);

    foreach (const WayPoint *wayPoint, m_wayPointsList)
        wayPoint->draw(&cachePainter);

    foreach (const Enemy *enemy, m_enemyList)
        enemy->draw(&cachePainter);

    foreach (const Bullet *bullet, m_bulletList)
        bullet->draw(&cachePainter);

    drawWave(&cachePainter);
    drawHP(&cachePainter);
    drawPlayerGold(&cachePainter);

    QPainter painter(this);
    painter.drawPixmap(0, 0, cachePix);
}

void MainWindow::mousePressEvent(QMouseEvent *event)
{
    QPoint pressPos = event->pos();
    auto it = m_towerPositionsList.begin();
    while (it != m_towerPositionsList.end())
    {


        if (canBuyTower() && it->containPoint(pressPos) && !it->hasTower())
        {        
            it->setHasTower();

            Tower *tower = new Tower(it->centerPos(), this);
            m_towersList.push_back(tower);
            update();
            break;
        }
        ++it;
    }

    for(int i = 0;i < m_towersList.size();i++){
        //设置攻击速度
        m_towersList.at(i)->setFireRate(200);
    }
}

bool MainWindow::canBuyTower() const
{
    if (m_playrGold >= TowerCost)
        return true;
    return false;
}

void MainWindow::drawWave(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(400, 5, 100, 25), QString("WAVE : %1").arg(m_waves + 1));
}

void MainWindow::drawHP(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(30, 5, 100, 25), QString("HP : %1").arg(m_playerHp));
}

void MainWindow::drawPlayerGold(QPainter *painter)
{
    painter->setPen(QPen(Qt::red));
    painter->drawText(QRect(200, 5, 200, 25), QString("GOLD : %1").arg(m_playrGold));
}

void MainWindow::doGameOver()
{
    if (!m_gameEnded)
    {
        m_gameEnded = true;
        // 此处应该切换场景到结束场景
        // 暂时以打印替代,见paintEvent处理
    }
}

void MainWindow::awardGold(int gold)
{
    update();
}

void MainWindow::addWayPoints()
{
    if(checkPoint == 1){
        WayPoint *wayPoint1 = new WayPoint(QPoint(300, 790));
        m_wayPointsList.push_back(wayPoint1);

        WayPoint *wayPoint2 = new WayPoint(QPoint(1900, 790));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(1900, 490));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(300, 490));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(300, 200));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(1900, 200));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);
    }else{
        WayPoint *wayPoint0 = new WayPoint(QPoint(190, 255));
        m_wayPointsList.push_back(wayPoint0);

        WayPoint *wayPoint1 = new WayPoint(QPoint(425, 255));
        m_wayPointsList.push_back(wayPoint1);
        wayPoint1->setNextWayPoint(wayPoint0);

        WayPoint *wayPoint2 = new WayPoint(QPoint(425, 660));
        m_wayPointsList.push_back(wayPoint2);
        wayPoint2->setNextWayPoint(wayPoint1);

        WayPoint *wayPoint3 = new WayPoint(QPoint(710, 660));
        m_wayPointsList.push_back(wayPoint3);
        wayPoint3->setNextWayPoint(wayPoint2);

        WayPoint *wayPoint4 = new WayPoint(QPoint(710, 255));
        m_wayPointsList.push_back(wayPoint4);
        wayPoint4->setNextWayPoint(wayPoint3);

        WayPoint *wayPoint5 = new WayPoint(QPoint(1030, 255));
        m_wayPointsList.push_back(wayPoint5);
        wayPoint5->setNextWayPoint(wayPoint4);

        WayPoint *wayPoint6 = new WayPoint(QPoint(1030, 660));
        m_wayPointsList.push_back(wayPoint6);
        wayPoint6->setNextWayPoint(wayPoint5);

        WayPoint *wayPoint7 = new WayPoint(QPoint(1415, 660));
        m_wayPointsList.push_back(wayPoint7);
        wayPoint7->setNextWayPoint(wayPoint6);

        WayPoint *wayPoint8 = new WayPoint(QPoint(1415, 255));
        m_wayPointsList.push_back(wayPoint8);
        wayPoint8->setNextWayPoint(wayPoint7);

        WayPoint *wayPoint9 = new WayPoint(QPoint(1795, 255));
        m_wayPointsList.push_back(wayPoint9);
        wayPoint9->setNextWayPoint(wayPoint8);

        WayPoint *wayPoint10 = new WayPoint(QPoint(1795, 660));
        m_wayPointsList.push_back(wayPoint10);
        wayPoint10->setNextWayPoint(wayPoint9);

        WayPoint *wayPoint11 = new WayPoint(QPoint(2075, 660));
        m_wayPointsList.push_back(wayPoint11);
        wayPoint11->setNextWayPoint(wayPoint10);
    }
}

void MainWindow::getHpDamage(int damage/* = 1*/)
{
    m_playerHp -= damage;
    if (m_playerHp <= 0)
        doGameOver();
}

void MainWindow::removedEnemy(Enemy *enemy)
{
    Q_ASSERT(enemy);
    m_enemyList.removeOne(enemy);
    delete enemy;

    if (m_enemyList.empty())
    {
        ++m_waves;
        if (!loadWave())
        {
            m_gameWin = true;
            // 游戏胜利转到游戏胜利场景
            // 这里暂时以打印处理
        }
    }
}

void MainWindow::removedBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.removeOne(bullet);
    delete bullet;
}

void MainWindow::addBullet(Bullet *bullet)
{
    Q_ASSERT(bullet);

    m_bulletList.push_back(bullet);
}

void MainWindow::updateMap()
{
    foreach (Enemy *enemy, m_enemyList)
        enemy->move();
    foreach (Tower *tower, m_towersList)
        tower->checkEnemyInRange();
    update();
}

bool MainWindow::loadWave()
{
    QString imgstr;
    if(checkPoint == 1){
        imgstr = QString(":/image/enemy1.png");
    }else{
        imgstr = QString(":/image/enemy.png");
    }

    if (m_waves >=7/*m_wavesInfo.size()*/)
        return false;


    if(m_waves==0)
    {
        Enemy1 *enemy1 = new Enemy1(m_wayPointsList.back(), this,QPixmap(imgstr));
        m_enemyList.push_back(enemy1);
        QTimer::singleShot(1000, enemy1, SLOT(doActivate()));
        return true;
    }

    if(m_waves==1)
    {
        Enemy *enemy = new Enemy(m_wayPointsList.back(), this,QPixmap(imgstr));
        m_enemyList.push_back(enemy);
        QTimer::singleShot(1000, enemy, SLOT(doActivate()));
        Enemy *enemy2 = new Enemy(m_wayPointsList.back(), this,QPixmap(imgstr));
        m_enemyList.push_back(enemy2);
        QTimer::singleShot(3000, enemy2, SLOT(doActivate()));
        Enemy *enemy3 = new Enemy(m_wayPointsList.back(), this,QPixmap(imgstr));
        m_enemyList.push_back(enemy3);
        QTimer::singleShot(5000, enemy3, SLOT(doActivate()));
        return true;

    }

    if(m_waves==2)
    {
        int enemyStartInterval[] = { 1000, 3000, 5000, 7000, 9000, 11000 };
        for (int i = 0; i <20 ; i++)
        {
            Enemy *enemy3 = new Enemy(m_wayPointsList.back(), this,QPixmap(imgstr));
            m_enemyList.push_back(enemy3);
            QTimer::singleShot(enemyStartInterval[i], enemy3, SLOT(doActivate()));
        }

        return true;
    }
    if(m_waves==3)
    {
        int enemyStartInterval[] = { 1000, 2000, 3000, 4000, 5000, 6000 };
        for (int i = 0; i <20 ; i++)
        {
            Enemy *enemy3 = new Enemy(m_wayPointsList.back(), this,QPixmap(imgstr));
            m_enemyList.push_back(enemy3);
            QTimer::singleShot(enemyStartInterval[i], enemy3, SLOT(doActivate()));
        }
        Enemy1 *enemy222 = new Enemy1(m_wayPointsList.back(), this,QPixmap(imgstr));
        Enemy *enemy22=enemy222;
        m_enemyList.push_back(enemy22);
        QTimer::singleShot(10, enemy22, SLOT(doActivate()));

        return true;
    }

    if(m_waves==4)
    {
        int enemyStartInterval[] = { 1000, 2000, 3000, 4000, 5000, 6000 };
        for (int i = 0; i < 15 ; i++)
        {
            Enemy *enemy3 = new Enemy(m_wayPointsList.back(), this,QPixmap(imgstr));
            m_enemyList.push_back(enemy3);
            QTimer::singleShot(enemyStartInterval[i], enemy3, SLOT(doActivate()));
        }

        for(int j=0;j< 20;j++)
        {
            Enemy1 *enemy2 = new Enemy1(m_wayPointsList.back(), this,QPixmap(imgstr));
            m_enemyList.push_back(enemy2);
            QTimer::singleShot(8000, enemy2, SLOT(doActivate()));
        }
        return true;
    }
    return true;
}

QList<Enemy *> MainWindow::enemyList() const
{
    return m_enemyList;
}

void MainWindow::setCheckPoint(int value)
{
    checkPoint = value;
    loadTowerPositions();
    addWayPoints();
    timer->start(30);
    // 设置300ms后游戏启动
    QTimer::singleShot(300, this, SLOT(gameStart()));
}

void MainWindow::gameStart()
{
    loadWave();
    for(int i = 0;i < m_enemyList.size();i++){
        //设置移动速度
        m_enemyList.at(i)->setWalkingSpeed(3);
    }
}

void MainWindow::on_pushButton_clicked()
{
    towerch=new towerchoice;
    towerch->show();
}
