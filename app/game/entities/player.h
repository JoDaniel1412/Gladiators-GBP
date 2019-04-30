#ifndef PLAYER_H
#define PLAYER_H

#include "entity.h"
#include "util/math.h"
#include "cmath"

#include <QFrame>

class Player : public QFrame, Entity
{
    Q_OBJECT
public:
    Player(QWidget *parent = nullptr);

private:
    int x;
    int y;
    int speed;
    int acc;

    int maxSpeed;
    int maxAcc;

    // Entity interface
public:
    void update();
    void draw();
};

#endif // PLAYER_H
