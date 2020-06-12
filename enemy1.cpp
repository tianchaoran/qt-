#include "enemy.h"
#include "waypoint.h"
#include "tower.h"
#include "utility.h"
#include "mainwindow.h"
#include <QPainter>
#include <QColor>
#include <QDebug>
#include <QMatrix>
#include <QVector2D>
#include <QtMath>
#include <QTime>
#include <QPixmap>
#include <enemy1.h>
const QSize Enemy1::ms_fixedSize(52, 52);
static const int Health_Bar_Width = 20;
Enemy1::Enemy1(WayPoint *startWayPoint, MainWindow *game,const QPixmap &sprite):Enemy(startWayPoint, game,sprite)
{
    this->setmaxHP(100);
    this->setcurrentHp(100);
}
Enemy1::~Enemy1()
{
    m_attackedTowersList.clear();
    m_destinationWayPoint = NULL;
    m_game = NULL;
}

/*void Enemy1::draw(QPainter *painter) const
{

    if (!m_active)
        return;
    QPixmap sprite;
    sprite.load(":/image/enemy1.png");
    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 8, -ms_fixedSize.height()+20);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 4));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 4));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人

    painter->drawPixmap(offsetPoint, sprite);
    painter->restore();
}*/
void Enemy1::draw(QPainter *painter) const
{
    QTime timm= QTime::currentTime();
    int second = timm.second();
    QPixmap sprite;
    if (!m_active)
        return;

    painter->save();

    QPoint healthBarPoint = m_pos + QPoint(-Health_Bar_Width / 2 - 8, -ms_fixedSize.height()+20);
    // 绘制血条
    painter->setPen(Qt::NoPen);
    painter->setBrush(Qt::red);
    QRect healthBarBackRect(healthBarPoint, QSize(Health_Bar_Width, 4));
    painter->drawRect(healthBarBackRect);

    painter->setBrush(Qt::green);
    QRect healthBarRect(healthBarPoint, QSize((double)m_currentHp / m_maxHp * Health_Bar_Width, 4));
    painter->drawRect(healthBarRect);

    // 绘制偏转坐标,由中心+偏移=左上
    static const QPoint offsetPoint(-ms_fixedSize.width() / 2, -ms_fixedSize.height() / 2);
    painter->translate(m_pos);
    painter->rotate(m_rotationSprite);
    // 绘制敌人
    if(second%2==0){sprite.load(":/image/enemy.png");}
    if(second%2==1){sprite.load(":/image/enemymov.png");}
    painter->drawPixmap(offsetPoint, sprite);
    painter->restore();
}
