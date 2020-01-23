#ifndef PLAYFIELD_H
#define PLAYFIELD_H
#include <QList>
#include <QStringList>


class Playfield
{
public:
    Playfield();
    void field_printer();

private:
    QList<QStringList> field {};

    void field_constructor();
    void init_state();

};

#endif // PLAYFIELD_H
