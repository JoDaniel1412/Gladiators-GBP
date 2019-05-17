#include "player.h"
#include <QMovie>
#include <QLabel>

Player::Player(QWidget *parent) : QFrame (parent), grid(static_cast<Grid *>(parent))
{
    gladiator = nullptr;
    tag = "player";
    x = 0;
    y = 0;
    width = 50;
    height = 50;
    xAcc = 1;
    yAcc = 1;
    maxAcc = 2;
    canMove = true;
    target = nullptr;
    nodeIndex = 0;
//    setStyleSheet("image: url(:img/gladiatorRun.gif)");

    this->setStyleSheet("background-color:green;");
    this->setGeometry(x, y, width, height);
    this->show();
}

Player::~Player()
{

}

void Player::update()
{
    if (target == nullptr) nextTarget();
    if (canMove && target != nullptr) move();
}

int Player::getMaxSpeed(){
    int gladiatorSpeed = this->gladiator->getSpeed();
    return gladiatorSpeed;
}

void Player::draw()
{
}

void Player::collide()
{
    //canMove = false;
}

void Player::uncollide()
{
    canMove = true;
}

void Player::kill()
{
    GameController::getInstance()->removeEntity(this);
}

QRect Player::getRect()
{
    QRect rect(x, y, width, height);
    return rect;
}

int Player::getX() const
{
    return x;
}

void Player::setX(int value)
{
    x = value;
}

int Player::getY() const
{
    return y;
}

void Player::setY(int value)
{
    y = value;
}

QList<Node *> Player::getNodePath() const
{
    return nodePath;
}

void Player::setNodePath(const QList<Node *> &value)
{
    nodePath = value;
}

Gladiator *Player::getGladiator() const
{
    return gladiator;
}

void Player::setGladiator(Gladiator *value)
{
    gladiator = value;
    maxSpeed = this->getMaxSpeed();
    if(maxSpeed<=0){
        maxSpeed=1;
    }
}

void Player::mousePressEvent(QMouseEvent *)
{
    gladiatorPressed(gladiator);
}

int Player::getNodeIndex() const
{
    return nodeIndex;
}

void Player::setNodeIndex(int value)
{
    nodeIndex = value;
}

void Player::move()
{
    xSpeed = Math::clamp(0, maxSpeed, xSpeed + xAcc);
    ySpeed = Math::clamp(0, maxSpeed, ySpeed + yAcc);
    x = Math::approach(x, target->x(), xSpeed);
    y = Math::approach(y, target->y(), ySpeed);;
    
    QFrame::move(x, y);
    if (x == target->x() && y == target->y())
    {
        target = nullptr;
        if (nodeIndex == nodePath.size()) kill();  // Reaches final Node
    }
}

void Player::nextTarget()
{
    Node *node = nodePath.value(nodeIndex);
    QList<Tile *> tiles = grid->getTiles();
    for (Tile *tile : tiles)
    {
        if (tile->getNode() == node)
        {
            nodeIndex++;
            target = tile;
            break;
        }
    }
}