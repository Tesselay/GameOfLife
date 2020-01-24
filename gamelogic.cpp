#include "gamelogic.h"
#include "playfield.h"
#include "utilities.h"
#include <QDebug>

GameLogic::GameLogic()
{
    field = play_field.field_constructor(50);
    initialize_field();
}

void GameLogic::initialize_field() {

    // Blinker
//    field[12][7] = alive_cell;
//    field[12][8] = alive_cell;
//    field[12][9] = alive_cell;

    // Glider
//    field[13][7] = alive_cell;
//    field[13][8] = alive_cell;
//    field[13][9] = alive_cell;
//    field[12][9] = alive_cell;
//    field[11][8] = alive_cell;

    // Exploder
    field[22][12] = alive_cell;
    field[22][14] = alive_cell;
    field[22][16] = alive_cell;
    field[23][12] = alive_cell;
    field[23][16] = alive_cell;
    field[24][12] = alive_cell;
    field[24][16] = alive_cell;
    field[25][12] = alive_cell;
    field[25][16] = alive_cell;
    field[26][12] = alive_cell;
    field[26][14] = alive_cell;
    field[26][16] = alive_cell;
}

void GameLogic::next_step() {

    play_field.field_printer(field);
    rules();
    cells_enliven(next_round_alive);
    cells_kill(next_round_dead);
    next_round_alive.clear();
    next_round_dead.clear();
}

void GameLogic::rules() {

    QList<QList<int>> live_cells = live_cell_finder();
    for ( int i {0}; i < live_cells.size(); i++) {
        if ( neighbour_finder(live_cells[i]) == 2 || neighbour_finder(live_cells[i]) == 3) {
            next_round_alive.append(live_cells[i]);
        } else {
            next_round_dead.append(live_cells[i]);
        }
    }

    QList<QList<int>> dead_cells = dead_neighbour_finder(live_cells);
    for ( int i {0}; i < dead_cells.size(); i++) {
        if ( neighbour_finder(dead_cells[i]) == 3) {
            next_round_alive.append(dead_cells[i]);
        } else {
            next_round_dead.append(dead_cells[i]);
        }
    }

    next_round_alive = Utilities::remove_duplicates(next_round_alive);
    next_round_dead = Utilities::remove_duplicates(next_round_dead);
}

QList<QList<int>> GameLogic::dead_neighbour_finder(QList<QList<int>> live_cells) {
    /* finds dead neighbours of alive cells for consideration of the second rule. Has the drawback of needing
       a method to find and delete duplicates, which most likely will still be faster than just checking every
       dead cell. */

    QList<QList<int>> dead_cells {};
    for ( int i {0}; i < live_cells.size(); i++) {
        int pos_start_x {live_cells[i].at(0)};
        int pos_start_y {live_cells[i].at(1)};

        for ( int j {0}; j < 3; j++) {
            for ( int k {0}; k < 3; k++) {
                // Points at every position of an 3x3 grid around corresponding live cell (including live cell)
                int pos_checked_x {pos_start_x - 1 + j};
                int pos_checked_y {pos_start_y - 1 + k};

                if ( field[pos_checked_x][pos_checked_y] == dead_cell) {
                    QList<int> cell_location {};
                    cell_location.append(pos_checked_x);
                    cell_location.append(pos_checked_y);
                    dead_cells.append(cell_location);
                }
            }
        }
    }



    return dead_cells;
}

QList<QList<int>> GameLogic::live_cell_finder() {

    QList<QList<int>> live_cells {};
    for ( int i {0}; i < field.size(); i++) {
        for ( int j {0}; j < field[0].size(); j++) {
            if (field[i][j] == alive_cell) {
                QList<int> cell {};
                cell.append(i);
                cell.append(j);
                live_cells.append(cell);
            }
        }
    }

    return live_cells;
}

int GameLogic::neighbour_finder(QList<int> cell_location) {

    int pos_start_x {cell_location.at(0)};
    int pos_start_y {cell_location.at(1)};

    int alive_neighbours {0};
    if (field[pos_start_x][pos_start_y] == alive_cell) {
        alive_neighbours = -1;  // Set to '-1' if own state is ALIVE, since the following loop checks the complete 3x3 square and not only the neighbours of the cell
    }

    for ( int i {0}; i < 3; i++) {
        for ( int j {0}; j < 3; j++) {
            int pos_checked_x {pos_start_x - 1 + i};
            int pos_checked_y {pos_start_y - 1 + j};
            if ( field[pos_checked_x][pos_checked_y] == alive_cell) {
                alive_neighbours++;
            }

        }
    }

    return alive_neighbours;
}

void GameLogic::cells_enliven(QList<QList<int>> next_round_alive) {

    for ( int i {0}; i < next_round_alive.size(); i++) {
        field[next_round_alive[i].at(0)][next_round_alive[i].at(1)] = alive_cell;
    }


}

void GameLogic::cells_kill(QList<QList<int>> next_round_dead){

    for ( int i {0}; i < next_round_dead.size(); i++) {
        field[next_round_dead[i].at(0)][next_round_dead[i].at(1)] = dead_cell;
    }


}
