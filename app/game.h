/**
 * @file game.h
 * @version 1.0
 * @date 19/04/19 -
 * @authors angelortizv
 * @title
 * @brief
 */

#ifndef GAME_H
#define GAME_H

#include <QMainWindow>
#include "game/grid.h"
#include "game/gamecontroller.h"
#include "game/entities/player.h"
#include "game/entities/enemy.h"

namespace Ui {
class Game;
}

class Game : public QMainWindow
{
    Q_OBJECT

public:
    explicit Game(QWidget *parent = nullptr);
    ~Game();

private:
    Ui::Game *ui;
    Grid *grid;
    GameController *gameController;

    void loadGrid();

    // QWidget interface
protected:
    void resizeEvent(QResizeEvent *event);

private slots:
    void on_pushButton_clicked();
};

#endif // GAME_H