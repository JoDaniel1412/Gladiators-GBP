#ifndef GLADIATOR_H
#define GLADIATOR_H

#include <QString>

#include "json/jsonserializable.h"
#include "graph/node.h"


class Gladiator : public JsonSerializable
{
public:
    Gladiator();

    Gladiator(QString id,
    int age,
    int health,
    int resistanceUpperBody,
    int resistanceLowerBody,
    int dodgeChance,
    int i,
    int j);

    void write(QJsonObject &jsonObj) const;
    void read(const QJsonObject &jsonObj);

    QString getId() const;
    void setId(const QString &value);

    int getAge() const;
    void setAge(int value);

    int getHealth() const;
    void setHealth(int value);

    int getResistanceUpperBody() const;
    void setResistanceUpperBody(int value);

    int getResistanceLowerBody() const;
    void setResistanceLowerBody(int value);

    int getDodgeChance() const;
    void setDodgeChance(int value);

    int getI() const;
    void setI(int value);

    int getJ() const;
    void setJ(int value);

    QList<Node *> getNodePath() const;
    void setNodePath(const QList<Node *> &value);

private:
    QString id;
    int age;
    int health;
    int resistanceUpperBody;
    int resistanceLowerBody;
    int dodgeChance;
    int i;
    int j;
    QList<Node *> nodePath;
};

#endif // GLADIATOR_H
