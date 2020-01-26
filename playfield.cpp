#include "playfield.h"
#include <QTextStream>

Playfield::Playfield()
{
}

QList<QStringList> Playfield::field_constructor(int field_size, QString dead_cell) {

    QList<QStringList> field {};
    for ( int i {0}; i < field_size; i++) {

        QStringList row {};
        for ( int j {0}; j < field_size; j++) {
            row.append(dead_cell);
        }
        field.append(row);
    }

    return field;
}

void Playfield::field_printer(QList<QStringList> field) {
    QTextStream out(stdout);
    for ( int i {0}; i < field.size(); i++) {

        for ( int j {0}; j < field[0].size(); j++) {

            out << field[i][j];
            out.flush();
        }

        out << "\n";
        out.flush();
    }

}


