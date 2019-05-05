#include "arrow.h"
#include "game/entities/player.h"

Arrow::Arrow(QWidget *parent) : QFrame(parent)
{
    tag = "arrow";
    x = 0;
    y = 0;
    width = 10;
    height = 2;
    damage = 1;
    xSpeed = 0;
    ySpeed = 0;
    xAcc = 1;
    yAcc = 1;
    maxSpeed = 30;
    maxAcc = 2;
    target = nullptr;

    this->setStyleSheet("background-color:#EBF5EE;");
    this->setGeometry(x, y, width, height);
    this->show();
}

void Arrow::update()
{
    if (target != nullptr) move();
}

void Arrow::draw()
{

}

void Arrow::collide()
{
    qDebug() << "HIT";
    delete this;
}

void Arrow::uncollide()
{

}

QRect Arrow::getRect()
{
    QRect rect(x, y, width, height);
    return rect;
}

int Arrow::getX() const
{
    return x;
}

void Arrow::setX(int value)
{
    x = value;
}

int Arrow::getY() const
{
    return y;
}

void Arrow::setY(int value)
{
    y = value;
}

Entity *Arrow::getTarget() const
{
    return target;
}

void Arrow::setTarget(Entity *value)
{
    target = value;
}

void Arrow::move()
{
    Player *targetPlayer = static_cast<Player *>(target);
    xSpeed = Math::clamp(0, maxSpeed, xSpeed + xAcc);
    ySpeed = Math::clamp(0, maxSpeed, ySpeed + yAcc);
    x = Math::approach(x, targetPlayer->getX(), xSpeed);
    y = Math::approach(y, targetPlayer->getY(), ySpeed);;

    QFrame::move(x, y);
}
