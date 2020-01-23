#include "playfield.h"
#include <QTextStream>
#include <QProcess>

Playfield::Playfield()
{
    field = field_constructor(25);
}

QList<QStringList> Playfield::field_constructor(int field_size) {

    QList<QStringList> field {};
    for ( int i {0}; i < field_size; i++) {

        QStringList row {};
        for ( int j {0}; j < field_size; j++) {
            row.append("   ");
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


