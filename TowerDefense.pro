QT       += core gui multimedia

CONFIG += c++11
DESTDIR = $$PWD/bin

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TowerDefense
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    towerposition.cpp \
    tower.cpp \
    waypoint.cpp \
    enemy.cpp \
    bullet.cpp \
    plistreader.cpp \
    towerchoice.cpp \
    endwindow.cpp \
    startwindow.cpp \
    tower1.cpp \
    enemy1.cpp

HEADERS  += mainwindow.h \
    towerposition.h \
    tower.h \
    waypoint.h \
    utility.h \
    enemy.h \
    bullet.h \
    plistreader.h \
    towerchoice.h \
    endwindow.h \
    startwindow.h \
    tower1.h \
    enemy1.h

FORMS    += mainwindow.ui \
    towerchoice.ui \
    endwindow.ui \
    startwindow.ui

RESOURCES += \
    resource.qrc


DISTFILES +=
