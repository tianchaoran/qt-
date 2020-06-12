 #ifndef ENEMY_H
#define ENEMY_H

#include <QObject>
#include <QPoint>
#include <QSize>
#include <QPixmap>

class WayPoint;
class QPainter;
class MainWindow;
class Tower;

class Enemy : public QObject
{
	Q_OBJECT
public:
    Enemy(WayPoint *startWayPoint, MainWindow *game, const QPixmap &sprite);
	~Enemy();

    void draw(QPainter *painter) const;
	void move();
	void getDamage(int damage);
	void getRemoved();
	void getAttacked(Tower *attacker);
	void gotLostSight(Tower *attacker);
    void setWalkingSpeed(int);
	QPoint pos() const;
    int				m_maxHp;
    int				m_currentHp;
   qreal			m_rotationSprite;
    void setmaxHP(int m);
    void setcurrentHp(int m);
     QPoint			m_pos;
     WayPoint *		m_destinationWayPoint;
     MainWindow *	m_game;
     QList<Tower *>	m_attackedTowersList;
     bool			m_active;
     const QPixmap	m_sprite;
public slots:
     void doActivate();
private:

     qreal			m_walkingSpeed;
	static const QSize ms_fixedSize;
};

#endif // ENEMY_H
