#include "gamelogic.h"
#include "playfield.h"
#include <QDebug>

GameLogic::GameLogic()
{
    initialize_field(play_field.field);
}

void GameLogic::initialize_field(QList<QStringList> field) {

    play_field.field[12][7] = " X ";
    play_field.field[12][8] = " X ";
    play_field.field[12][9] = " X ";

}

void GameLogic::next_step() {

    play_field.field_printer(play_field.field);
    live_cell_finder(play_field.field);
}

void GameLogic::rules(QList<QStringList> field) {



}

QList<QList<int>> GameLogic::live_cell_finder(QList<QStringList> field) {

    QList<QList<int>> live_cells {};
    for ( int i {0}; i < field.size(); i++) {
        for ( int j {0}; j < field[0].size(); j++) {
            if (field[i][j] == " X ") {
                QList<int> cell {};
                cell.append(i);
                cell.append(j);
                live_cells.append(cell);
            }
        }
    }

    return live_cells;
}
