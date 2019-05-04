#include "tile.h"

Tile::Tile(QWidget *parent, int i, int j) : QFrame(parent)
{
    this->i = i;
    this->j = j;
    this->node = nullptr;
    this->build = false;
}

void Tile::setup(QChar qchar)
{
    if (qchar != '.') node->setOccupied(true);
    else setStyleSheet("background-color:#8B786D;");  // Road

    if (qchar == '0') setStyleSheet("background-color:#504b58;");  // Wall
    if (qchar == 'B'){  // Build
        build = true;
        setStyleSheet("background-color:#635255;"
                      "image: url(:img/buildIcon.png)");
    }

}

int Tile::getI() const
{
    return i;
}

int Tile::getJ() const
{
    return j;
}

QRect Tile::getRect() const
{
    QRect rect(x(), y(), width(), height());
    return rect;
}

Node *Tile::getNode() const
{
    return node;
}

void Tile::setNode(Node *value)
{
    node = value;
}

bool Tile::canBuild() const
{
    return build;
}

void Tile::setCanBuild(bool value)
{
    build = value;
}
