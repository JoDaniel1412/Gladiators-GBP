#include "gladiator.h"

Gladiator::Gladiator()
{
    id = "";
    age = 0;
    health = 0;
    resistanceUpperBody = 0;
    resistanceLowerBody = 0;
    dodgeChance = 0;
    i = 0;
    j = 0;
    startHealth = 0;
    alive = true;
    Boss = false;
}

Gladiator::Gladiator(QString id, int age, int health, int resistanceUpperBody, int resistanceLowerBody, int dodgeChance, int i, int j)
{
    this->id = id;
    this->age = age;
    this->health = health;
    this->resistanceUpperBody = resistanceUpperBody;
    this->resistanceLowerBody = resistanceLowerBody;
    this->dodgeChance = dodgeChance;
    this->i= i;
    this->j = j;
    startHealth = health;
    alive = true;
    Boss = false;
}

int Gladiator::getSpeed(){
    if(Boss){
        return 5;
    }else{
        int speed = 0;
        speed += this->getResistanceLowerBody();
        speed -= this->getResistanceUpperBody()/2;
        return speed;
    }
}

void Gladiator::write(QJsonObject &jsonObj) const
{
    jsonObj["id"] = id;
    jsonObj["age"] = age;
    jsonObj["health"] = startHealth;
    jsonObj["resistanceUpperBody"] = resistanceUpperBody;
    jsonObj["resistanceLowerBody"] = resistanceLowerBody;
    jsonObj["dodgeChance"] = dodgeChance;
}

void Gladiator::read(const QJsonObject &jsonObj)
{
    id = jsonObj["id"].toString();
    age = jsonObj["age"].toInt();
    health = jsonObj["health"].toInt();
    resistanceUpperBody = jsonObj["resistanceUpperBody"].toInt();
    resistanceLowerBody = jsonObj["resistanceLowerBody"].toInt();
    dodgeChance = jsonObj["dodgeChance"].toInt();

    if (health <= 0) health = 1;
    startHealth = health;
}

QString Gladiator::getId() const
{
    return id;
}

void Gladiator::setId(const QString &value)
{
    id = value;
}

int Gladiator::getAge() const
{
    return age;
}

void Gladiator::setAge(int value)
{
    age = value;
}

int Gladiator::getHealth() const
{
    return health;
}

void Gladiator::setHealth(int value)
{
    health = value;
}

int Gladiator::getResistanceUpperBody() const
{
    return resistanceUpperBody;
}

void Gladiator::setResistanceUpperBody(int value)
{
    resistanceUpperBody = value;
}

int Gladiator::getResistanceLowerBody() const
{
    return resistanceLowerBody;
}

void Gladiator::setResistanceLowerBody(int value)
{
    resistanceLowerBody = value;
}

int Gladiator::getDodgeChance() const
{
    return dodgeChance;
}

void Gladiator::setDodgeChance(int value)
{
    dodgeChance = value;
}

int Gladiator::getI() const
{
    return i;
}

void Gladiator::setI(int value)
{
    i = value;
}

int Gladiator::getJ() const
{
    return j;
}

void Gladiator::setJ(int value)
{
    j = value;
}

QList<Node *> Gladiator::getNodePath() const
{
    return nodePath;
}

void Gladiator::setNodePath(const QList<Node *> &value)
{
    nodePath = value;
}

int Gladiator::getStartHealth() const
{
    return startHealth;
}

void Gladiator::setStartHealth(int value)
{
    startHealth = value;
}

bool Gladiator::getBoss() const
{
    return Boss;
}

void Gladiator::setBoss(bool value)
{
    Boss = value;
}


bool Gladiator::isAlive() const
{
    return alive;
}

void Gladiator::setAlive(bool value)
{
    alive = value;
}

int Gladiator::getThoughness(){
    if(Boss){
        return 5000;
    }else{
        int thoughness = 0;
        thoughness += this->getResistanceUpperBody();
        thoughness -= this->getResistanceLowerBody() / 2;
        if (thoughness < 0) thoughness = 0;
        return thoughness;
    }
}
