#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QStringList>
#include <QTextStream>
#include <QList>
#include <tuple>
#include "playfield.h"
#include "utilities.h"

class GameLogic
{
public:
    GameLogic();
    void next_step();

    // Public for access from the unit test
    QString dead_cell {" _ "};
    int field_size {25};

private:
    Playfield play_field;

    QList<QList<QList<int>>> presets {};
    QStringList preset_names {};
    QString alive_cell {" X "};
    QList<QStringList> field {};
    // Alive/dead cells of next round are saved in list to stage them for appliance after all calculations are done
    QList<QList<int>> next_round_alive {};
    QList<QList<int>> next_round_dead {};

    void initialize_field();
    void initialize_presets();
    QString custom_pattern();       // Return is there for 'Cancel'-option to take back user to the preset menu
    void rules();
    QList<QList<int>> live_cell_finder();
    QList<QList<int>> dead_neighbour_finder(QList<QList<int>> live_cells);
    int neighbour_finder(QList<int> location);
    std::tuple<int, int> boundary_overstep(int pos_x, int pos_y);
    void cells_enliven(QList<QList<int>> next_round_alive);
    void cells_kill(QList<QList<int>> next_round_dead);
};

#endif // GAMELOGIC_H
