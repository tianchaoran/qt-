#ifndef ENEMY1_H
#define ENEMY1_H
#include<enemy.h>

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;
class Enemy1 : public Enemy
{
public:
    Enemy1();
    Enemy1(WayPoint *startWayPoint, MainWindow *game,const QPixmap &sprite);
    virtual  ~Enemy1();
    void draw(QPainter *painter) const;
    static const QSize ms_fixedSize;
};



#endif // ENEMY1_H
