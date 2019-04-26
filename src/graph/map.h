#ifndef MAP_H
#define MAP_H

#include <QList>

#include "node.h"

class Map
{
public:
    static Map *getInstance();

    void reSizeMatrix(int rows, int columns);

    void clearMatrix();

    Node *nodeAt(int row, int column);

    QPair<int, int> indexOf(Node *node);

    QList<QList<Node *> *> *getMatrix() const;
    void setMatrix(QList<QList<Node *> *> *value);

    int getRows() const;

    int getColumns() const;

private:
    static Map *instance;
    int rows;
    int columns;
    QList<QList<Node *> *> *matrix;

    Map();

    void load();

    void loadMatrix();

    void loadNeighbors();

    void loadNeighbors(int i, int j, Node *node);
};

#endif // MAP_H
