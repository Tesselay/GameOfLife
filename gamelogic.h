#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QStringList>
#include <QList>
#include "playfield.h"

class GameLogic
{
public:
    GameLogic();
    void next_step();

    // Initialized public for access for the unit test
    QString alive_cell {" X "};
    QString dead_cell {" = "};
    int field_size {15};

private:
    Playfield play_field;

    QList<QStringList> field {};
    // Alive/dead cells of next round are saved in list to stage them for appliance after all calculations are done
    QList<QList<int>> next_round_alive {};
    QList<QList<int>> next_round_dead {};

    void initialize_field();
    void rules();
    QList<QList<int>> live_cell_finder();
    QList<QList<int>> dead_neighbour_finder(QList<QList<int>> live_cells);
    int neighbour_finder(QList<int> location);
    void cells_enliven(QList<QList<int>> next_round_alive);
    void cells_kill(QList<QList<int>> next_round_dead);
};

#endif // GAMELOGIC_H
