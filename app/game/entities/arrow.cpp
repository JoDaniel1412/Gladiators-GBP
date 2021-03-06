#include "arrow.h"
#include "game/entities/player.h"
#include "game/entities/gladiator.h"
#include "game/grid.h"

Arrow::Arrow(QWidget *parent, int x, int y) : QFrame(parent)
{
    tag = "arrow";
    this->x = x;
    this->y = y;
    width = 10;
    height = 10;
    damage = 10;
    xSpeed = 0;
    ySpeed = 0;
    xAcc = 1;
    yAcc = 1;
    maxSpeed = 60;
    maxAcc = 10;
    target = nullptr;

    setStyleSheet("background-color:255,255,255,0;"
                  "image: url(:/img/fire/00fire.png)");

    //    this->setStyleSheet("background-color:#EBF5EE;");
    this->setGeometry(x, y, width, height);
    this->show();
}

void Arrow::setDamage(int Damage){
    this->damage = Damage;
}

int Arrow::getDamage(){
    return this->damage;
}

Arrow::~Arrow()
{

}

void Arrow::update()
{
    if (target != nullptr) move();
    else GameController::getInstance()->removeEntity(this);
}

void Arrow::draw()
{

}

void createBoss(Player *player){
    Gladiator *tempGladiator = new Gladiator();
    tempGladiator->setDodgeChance(player->getGladiator()->getDodgeChance());
    tempGladiator->setResistanceLowerBody(player->getGladiator()->getResistanceLowerBody());
    tempGladiator->setResistanceUpperBody(player->getGladiator()->getResistanceUpperBody());
    Spawner::getInstance()->setTempGladiator(tempGladiator);
    player->getGladiator()->setHealth(floor(50 * Spawner::getInstance()->getBossHealthIncrease()));
    player->getGladiator()->setDodgeChance(0);
    player->getGladiator()->setBoss(true);
    player->getGladiator()->setResistanceLowerBody(00);
    player->getGladiator()->setResistanceUpperBody(00);
    Spawner::getInstance()->setBossHealthIncrease(Spawner::getInstance()->getBossHealthIncrease() + 0.2);
}

void Arrow::collide()
{
    int damageDone = tower->getDamagePerShoot();
    for (Entity *entity : GameController::getInstance()->getEntities())
    {
        if (entity->tag == "player" &&
                Collision::collide(getRect(), entity->getRect()))
        {
            if (tower->getType() != 3)
            {
                Player *player = dynamic_cast<Player *>(entity);
                player->hit(damageDone);
                int health = player->getGladiator()->getHealth();
                if (health <= 0 && !(Spawner::getInstance()->getBossON()) && !(player->getGladiator()->getBoss())) playerKill();
                else if(health <= 0 && Spawner::getInstance()->getBossON()){
                    Spawner::getInstance()->setBossON(false);

                    setStyleSheet("background-color: rgba(255,255,255,0);");
                    player->movie()->stop();
                    QMovie *movie = new QMovie(player);
                    delete player->movie();
                    movie->setFileName(":/img/MinotaurRun.gif");
                    movie->setScaledSize(player->size());
                    player->setMovie(movie);
                    movie->start();

//                    player->setStyleSheet("background-color:255,255,255,0;"
//                                          "image: url(:/img/MinotaurRun.gif)");
                    createBoss(player);
                    QMediaPlayer* exit = new QMediaPlayer;
                    exit->setMedia(QUrl("qrc:/audio/minotaur.mp3"));
                    exit->setVolume(100);
                    exit->play();

                }else if(health <= 0){
                    playerKill();
                }
            }
            else
            {
                QList<Entity *> playersHit = AOECollide();
                for (Entity *entity : playersHit) {
                    Player *tempPlayer = dynamic_cast<Player *>(entity);
                    tempPlayer->hit(damageDone);
                    int health = tempPlayer->getGladiator()->getHealth();
                    if (health <= 0) playerKill();
                    if (health <= 0 && !(Spawner::getInstance()->getBossON()) && !(tempPlayer->getGladiator()->getBoss())) playerKill();
                    else if(health <= 0 && Spawner::getInstance()->getBossON()){
                        Spawner::getInstance()->setBossON(false);
                        tempPlayer->setStyleSheet("background-color:255,255,255,0;"
                                              "image: url(:/img/MinotaurRun.gif)");
                        createBoss(tempPlayer);
                        QMediaPlayer* exit = new QMediaPlayer;
                        exit->setMedia(QUrl("qrc:/audio/minotaur.mp3"));
                        exit->setVolume(100);
                        exit->play();
                    }else if(health <= 0){
                        playerKill();
                    }
                }
                playersHit.clear();
                areaDamageEffect();
            }
            kill();
            break;
        }
    }
}

void Arrow::uncollide()
{

}

QRect Arrow::getRect()
{
    QRect rect(x, y, width, height);
    return rect;
}

void Arrow::kill()
{
    GameController::getInstance()->removeEntity(this);
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

void Arrow::setTower(Tower *value)
{
    tower = value;
}

Entity *Arrow::getParent() const
{
    return parentEnemy;
}

void Arrow::setParent(Entity *value)
{
    parentEnemy = value;
}

void Arrow::move()
{
    if (target == nullptr || target->tag != "player") return;

    int offset = 10;
    Player *targetPlayer = static_cast<Player *>(target);
    xSpeed = Math::clamp(0, maxSpeed, xSpeed + xAcc);
    ySpeed = Math::clamp(0, maxSpeed, ySpeed + yAcc);
    x = Math::approach(x, targetPlayer->getX() + offset, xSpeed);
    y = Math::approach(y, targetPlayer->getY() + offset, ySpeed);;

    QFrame::move(x, y);
}

void Arrow::playerKill()
{
    tower->setXp(tower->getXp() + 1);
    Enemy *enemy = dynamic_cast<Enemy *>(parentEnemy);
    enemy->playerKill();
}

void Arrow::areaDamageEffect()
{
    Grid *grid = dynamic_cast<Grid *>(parent());
//    QFrame *qFrame = new QFrame(grid);
//    qFrame->setStyleSheet("background-color:#635255;");
    int xPoss = x - grid->getTileSize();
    int yPoss = y - grid->getTileSize();
    int diameter = grid->getTileSize() * 3;
//    qFrame->setGeometry(xPoss,yPoss,diameter,diameter);
//    qFrame->show();

    QMovie *movie = new QMovie(":/img/implosion.gif");
    QLabel *processLabel = new QLabel(grid);
    processLabel->setMovie(movie);
    processLabel->setStyleSheet("background-color: rgba(255,255,255,0);");
    processLabel->setGeometry(xPoss, yPoss, diameter,diameter);
    movie->setScaledSize(processLabel->size());
    movie->start();
    processLabel->show();

    QTimer::singleShot(200, processLabel, &QFrame::close);
}

QRegion Arrow::getCircle()
{
    Grid *grid = dynamic_cast<Grid *>(parent());
    int xPoss = x - grid->getTileSize();
    int yPoss = y - grid->getTileSize();
    int diameter = grid->getTileSize() * 3;
    QRegion circle(xPoss, yPoss, diameter, diameter, QRegion::Ellipse);
    return circle;
}

QList<Entity *> Arrow::AOECollide(){
    QList<Entity *> players;
    for (Entity *entity : GameController::getInstance()->getEntities())
    {
        if (entity->tag == "player" &&
                Collision::collide(getCircle(), entity->getRect()))
        {
            players.push_back(entity);
        }
    }
    return players;
}

