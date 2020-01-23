#include "gamelogic.h"
#include "playfield.h"
#include <QDebug>

GameLogic::GameLogic()
{
    initialize_field(play_field.field);
}

void GameLogic::initialize_field(QList<QStringList> field) {

    // Blinker
    play_field.field[12][7] = " X ";
    play_field.field[12][8] = " X ";
    play_field.field[12][9] = " X ";

}

void GameLogic::next_step() {

    play_field.field_printer(play_field.field);
    rules(play_field.field);
}

void GameLogic::rules(QList<QStringList> field) {

    QList<QList<int>> live_cells = live_cell_finder(play_field.field);
    for ( int i {0}; i < live_cells.size(); i++) {
        qDebug() << "Amount of neighbours: " << neighbour_finder(live_cells[i], play_field.field);

    }

}

int GameLogic::neighbour_finder(QList<int> cell_location, QList<QStringList> field) {

    int pos_start_x {cell_location.at(0)};
    int pos_start_y {cell_location.at(1)};

    int alive_neighbours {-1};  // Init as '-1' since the following loop checks the complete 3x3 square and not only the neighbours of the cell

    for ( int i {0}; i < 3; i++) {
        for ( int j {0}; j < 3; j++) {
            if ( field[pos_start_x - 1 + i][pos_start_y - 1 + j] == " X ") {
                alive_neighbours++;
            }
        }
    }

    return alive_neighbours;
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
