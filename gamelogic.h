#ifndef GAMELOGIC_H
#define GAMELOGIC_H
#include <QStringList>
#include <QList>
#include <playfield.h>

class GameLogic
{
public:
    GameLogic();
    void next_step();

private:
    Playfield play_field;

    void initialize_field(QList<QStringList> field);
    void rules(QList<QStringList> field);
    QList<QList<int>> live_cell_finder(QList<QStringList> field);
};

#endif // GAMELOGIC_H
