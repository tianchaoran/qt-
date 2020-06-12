#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QList>
#include "towerposition.h"
#include "tower.h"
#include "towerchoice.h"
#include "endwindow.h"
namespace Ui {
class MainWindow;
}

class WayPoint;
class Enemy;
class Enemy1;
class Bullet;
class Endwindow;

class MainWindow : public QMainWindow
{
	Q_OBJECT
	
public:
	explicit MainWindow(QWidget *parent = 0);
	~MainWindow();

	void getHpDamage(int damage = 1);
	void removedEnemy(Enemy *enemy);
	void removedBullet(Bullet *bullet);
	void addBullet(Bullet *bullet);
	void awardGold(int gold);

	QList<Enemy *> enemyList() const;
    towerchoice *towerch;
    Endwindow *ew;
    void setCheckPoint(int);

protected:
	void paintEvent(QPaintEvent *);
	void mousePressEvent(QMouseEvent *);


public slots:
    void gameStart();

private slots:
	void updateMap();
    void on_pushButton_clicked();

private:
	void loadTowerPositions();
	void addWayPoints();
	bool loadWave();
	bool canBuyTower() const;
	void drawWave(QPainter *painter);
	void drawHP(QPainter *painter);
	void drawPlayerGold(QPainter *painter);
	void doGameOver();
	void preLoadWavesInfo();

private:
	Ui::MainWindow *		ui;
    int						m_waves=0;
	int						m_playerHp;
	int						m_playrGold;
	bool					m_gameEnded;
	bool					m_gameWin;
	QList<TowerPosition>	m_towerPositionsList;
	QList<Tower *>			m_towersList;
	QList<WayPoint *>		m_wayPointsList;
	QList<Enemy *>			m_enemyList;
	QList<Bullet *>			m_bulletList;
    int checkPoint;
    QTimer *timer;
};

#endif // MAINWINDOW_H
