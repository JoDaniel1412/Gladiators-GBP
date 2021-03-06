#include "spawner.h"

#include "game/entities/player.h"
#include "game/entities/enemy.h"

Spawner *Spawner::instance = nullptr;

Spawner *Spawner::getInstance(QObject *parent)
{
    if (instance == nullptr) instance = new Spawner(parent);
    return instance;
}

void Spawner::stop()
{
    gladiators->clear();
}

void Spawner::spawnGladiators(QList<Gladiator *> *value)
{
    gladiators = new QList<Gladiator *>(*value);
    gameController->setWaveActive(true);
    spawn();
}

void Spawner::spawnTower(Tile *tile, Tower *tower)
{
    Grid *grid = dynamic_cast<Grid *>(parent);
    int tileSize = grid->getTileSize();
    int x = tile->x();
    int y = tile->y();

    Enemy *enemy = new Enemy(grid, x, y);
    enemy->resize(tileSize, tileSize);
    enemy->setTower(tower);
    enemy->updateDelta();

    Entity *entity = enemy;
    gameController->addEntity(entity);
    tile->getNode()->setEntity(entity);
}

void Spawner::spawnArrow(int x, int y, Entity *target, int towerDamage, Enemy *tower)
{
    Grid *grid = dynamic_cast<Grid *>(parent);

    Arrow *arrow = new Arrow(grid, x, y);
    arrow->setParent(tower);
    arrow->setTower(tower->getTower());
    arrow->setTarget(target);
    arrow->setDamage(towerDamage);


    Entity *entity = arrow;
    gameController->addEntity(entity);
}

int Spawner::waveSize()
{
    return gladiators->size();
}

bool Spawner::isWaveFinished()
{
    return gladiators->isEmpty();
}

void Spawner::spawn()
{
    if (gladiators->isEmpty()) return;
    if (gameController->isPause()) {
        QTimer::singleShot(spawnDelay, this, &Spawner::spawn);
        return;
    }

    // Generates the player
    Grid *grid = dynamic_cast<Grid *>(parent);
    Player *player = new Player(grid);
    Gladiator *gladiator = gladiators->takeFirst();
    player->setGladiator(gladiator);
    player->setNodePath(gladiator->getNodePath());
    int size = grid->getTileSize();
    player->resize(size, size);

    Entity *entity = player;
    gameController->addEntity(entity);

    // Recursive call
    QTimer::singleShot(spawnDelay, this, &Spawner::spawn);
}

int Spawner::getEnemiesOver() const
{
    return enemiesOver;
}

void Spawner::setEnemiesOver(int value)
{
    enemiesOver = value;
}

float Spawner::getBossHealthIncrease() const
{
    return bossHealthIncrease;
}

void Spawner::setBossHealthIncrease(float value)
{
    bossHealthIncrease = value;
}

Gladiator *Spawner::getTempGladiator() const
{
    return tempGladiator;
}

void Spawner::setTempGladiator(Gladiator *value)
{
    tempGladiator = value;
}

bool Spawner::getBossON() const
{
    return bossON;
}

void Spawner::setBossON(bool value)
{
    bossON = value;
}

int Spawner::getSpawnDelay() const
{
    return spawnDelay;
}

void Spawner::setSpawnDelay(int value)
{
    spawnDelay = value;
}

void Spawner::setParent(QObject *value)
{
    parent = value;
}

Spawner::Spawner(QObject *parent) : QObject (parent), parent(parent)
{
    gameController = GameController::getInstance();
    spawnDelay = 500;
    gladiators = new QList<Gladiator *>();
    tempGladiator = nullptr;
    bossON = false;
    bossHealthIncrease = 1.0;
}
