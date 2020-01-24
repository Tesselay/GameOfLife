#ifndef PLAYFIELD_H
#define PLAYFIELD_H
#include <QList>
#include <QStringList>


class Playfield
{
public:
    Playfield();

    void field_printer(QList<QStringList> field);
    QList<QStringList> field_constructor(int field_size, QString dead_cell);



};

#endif // PLAYFIELD_H
