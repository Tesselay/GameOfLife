#include "gamelogic.h"

#include <QDebug>

GameLogic::GameLogic()
{
    field = play_field.field_constructor(field_size, dead_cell);
    initialize_presets();
    initialize_field();
}

void GameLogic::initialize_field() {
    QTextStream in(stdin);
    QTextStream out(stdout);

    QString user_input {};
    int preset_amount {presets.size()};     // Saved as variable to save calculation time
    while ( !( user_input.toInt() <= preset_amount && user_input.toInt() > 0 ) && user_input != 'x') {
        out << "Choose one of the presets:\n";
        out.flush();

        for ( int i {0}; i < preset_amount; i++) {
            out << "[" << i+1 << "] " << preset_names.at(i) << "\n";
            out.flush();
        }
        out << "[x] Custom pattern\n";
        out.flush();

        out << "\n> ";
        out.flush();
        in >> user_input;
        in.flush();

        if ( user_input.toInt() <= preset_amount && user_input.toInt() > 0 ) {
            for ( int i {0}; i < presets.at(user_input.toInt() - 1).size(); i++ ) {
                field[ presets[user_input.toInt() - 1][i][0] ][ presets[user_input.toInt() - 1][i][1] ] = alive_cell;       // '-1' since user choice begins at 1
            }
        } else if ( user_input.toLower() == 'x' ) {
            user_input = custom_pattern();
        }
    }

    Utilities::clear_screen();
}

QString GameLogic::custom_pattern() {
    QTextStream in(stdin);
    QTextStream out(stdout);

    QString x {};
    QString y {};
    QString other_option {};
    // saves for location of choosen cell for 'Undo'-option
    int x_before {};
    int y_before {};
    while ( (x != 'f') && (x != 'c') ) {
        play_field.field_printer(field);

        out << "\nInput values for x (horizontal & menu-option) and y (vertical), e.g.: 'x y: 10 10' or 'x y: f f'\n[f] Finish\n[u] Undo\n[c] Cancel\n";
        out.flush();
        out << "x y: ";
        out.flush();
        in >> x >> y;

        if ( (x.toInt() > 0 && x.toInt() < field.size()) && (y.toInt() > 0 && y.toInt() < field[0].size()) ){
            field[x.toInt() - 1][y.toInt() - 1] = alive_cell;
            x_before = x.toInt() - 1;
            y_before = y.toInt() - 1;
        } else if ( x.toLower() == 'f') {
            Utilities::clear_screen();
            return "x";
        } else if ( x.toLower() == 'u') {
            field[x_before][y_before] = dead_cell;
        } else if ( x.toLower() == 'c') {
            Utilities::clear_screen();
            field = play_field.field_constructor(field_size, dead_cell);
            return "n";
        }
        Utilities::clear_screen();

    }
}

void GameLogic::initialize_presets() {

    QList<QList<int>> blinker {{12,7},{12,8},{12,9}};
    QList<QList<int>> glider {{22,7},{22,8},{22,9},{21,9},{20,8}};
    QList<QList<int>> exploder {{12,12},{12,14},{12,16},{13,12},{13,16},{14,12},{14,16},{15,12},{15,16},{16,12},{16,14},{16,16}};
    QList<QList<int>> pulsator {{12,7},{12,8},{12,9},{12,10},{12,11},{12,12},{12,13},{12,14},{12,15},{12,16}};

    presets.append(blinker);
    preset_names.append("Blinker");
    presets.append(glider);
    preset_names.append("Glider");
    presets.append(exploder);
    preset_names.append("Exploder");
    presets.append(pulsator);
    preset_names.append("Pulsator");


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
        // Applies rules to all alive cells and either marks them for alive or dead
        if ( neighbour_finder(live_cells[i]) == 2 || neighbour_finder(live_cells[i]) == 3) {
            next_round_alive.append(live_cells[i]);
        } else {
            next_round_dead.append(live_cells[i]);
        }
    }

    QList<QList<int>> dead_cells = dead_neighbour_finder(live_cells);
    for ( int i {0}; i < dead_cells.size(); i++) {
        // Applies rules to all dead cells neighbour to alive cells and either marks them for alive or dead
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

    int pos_start_x {};
    int pos_start_y {};
    int pos_checked_x {};
    int pos_checked_y {};
    QList<QList<int>> dead_cells {};
    for ( int i {0}; i < live_cells.size(); i++) {
        pos_start_x = live_cells[i].at(0);
        pos_start_y = live_cells[i].at(1);

        for ( int j {0}; j < 3; j++) {
            for ( int k {0}; k < 3; k++) {
                // Points at every position of an 3x3 grid around corresponding live cell (including live cell)
                pos_checked_x = pos_start_x - 1 + j;
                pos_checked_y = pos_start_y - 1 + k;

                std::tie(pos_checked_x, pos_checked_y) = boundary_overstep(pos_checked_x, pos_checked_y);

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

int GameLogic::neighbour_finder(QList<int> cell_location) {

    int pos_start_x {cell_location.at(0)};
    int pos_start_y {cell_location.at(1)};

    int alive_neighbours {0};
    if (field[pos_start_x][pos_start_y] == alive_cell) {
        alive_neighbours = -1;  // Set to '-1' if own state is ALIVE, since the following loop checks the complete 3x3 square and not only the neighbours of the cell
    }

    int pos_checked_x {};
    int pos_checked_y {};
    for ( int i {0}; i < 3; i++) {
        for ( int j {0}; j < 3; j++) {
            pos_checked_x = pos_start_x - 1 + i;
            pos_checked_y = pos_start_y - 1 + j;

            std::tie(pos_checked_x, pos_checked_y) = boundary_overstep(pos_checked_x, pos_checked_y);

            if ( field[pos_checked_x][pos_checked_y] == alive_cell) {
                alive_neighbours++;
            }
        }
    }

    return alive_neighbours;
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

std::tuple<int, int> GameLogic::boundary_overstep(int pos_x, int pos_y) {

    if ( pos_x < 0  ) {
        pos_x = pos_x + (field.size());
    } else if ( pos_x >= field.size() ) {
        pos_x = (field.size()) - pos_x;
    }

    if ( pos_y < 0 ) {
        pos_y = pos_y + (field[pos_x].size());
    } else if (pos_y >= field[pos_x].size() ) {
        pos_y = (field[pos_x].size()) - pos_y;
    }

    return std::make_tuple(pos_x, pos_y);

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
