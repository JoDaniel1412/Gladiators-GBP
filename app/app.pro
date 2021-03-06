#-------------------------------------------------
#
# Project created by QtCreator 2019-04-16T10:54:48
#
#-------------------------------------------------
include(../defaults.pri)

QT       += core gui
QT += multimedia

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = app
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
#DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0

CONFIG += c++11

SOURCES += \
	game/entities/arrow.cpp \
	game/grid.cpp \
	game/spawner.cpp \
	game/tile.cpp \
        main.cpp \
        mainwindow.cpp \
    settings.cpp \
    pregame.cpp \
    game.cpp \
    game/entities/player.cpp \
    game/gamecontroller.cpp \
    game/entities/enemy.cpp \
    util.cpp \
    game/entities/spell.cpp \
    gameover.cpp

HEADERS += \
	game/entities/arrow.h \
	game/grid.h \
	game/spawner.h \
	game/tile.h \
        mainwindow.h \
    settings.h \
    pregame.h \
    game/entities/player.h \
    game/entities/entity.h \
    game/gamecontroller.h \
    game.h \
    game/entities/enemy.h \
    util.h \
    game/entities/spell.h \
    gameover.h

FORMS += \
        mainwindow.ui \
    settings.ui \
    pregame.ui \
    game.ui \
    gameover.ui

LIBS += -L../src -lmylib

# Default rules for deployment.
qnx: target.path = /tmp/$${TARGET}/bin
else: unix:!android: target.path = /opt/$${TARGET}/bin
!isEmpty(target.path): INSTALLS += target

RESOURCES += \
    imgresources.qrc \
    mapresources.qrc \
    audioresources.qrc

