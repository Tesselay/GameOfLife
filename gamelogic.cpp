#include "gamelogic.h"
#include "playfield.h"
#include <QDebug>

GameLogic::GameLogic()
{
    initialize_field(play_field.field);
}

void GameLogic::initialize_field(QList<QStringList> field) {

    qDebug() << play_field.field[0].size();
    qDebug() << play_field.field.size();

}

void GameLogic::next_step() {



}

void GameLogic::rules(QList<QStringList> field) {



}
