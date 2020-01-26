#include "playfield.h"

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

    // Prints top index bar
    out << "   ";
    out.flush();
    for ( int j {0}; j < field[0].size(); j++) {
        if ( j < 9) {
            out << " " << j+1 << " ";
            out.flush();
        } else {
            out << " " << j+1;
            out.flush();
        }
    }
    out << "\n";
    out.flush();

    for ( int i {0}; i < field.size(); i++) {

        // Prints left index bar
        if ( i < 9) {
            out << " " << i+1 << " ";
            out.flush();
        } else {
            out << i+1 << " ";
            out.flush();
        }


        for ( int j {0}; j < field[i].size(); j++) {
            out << field[i][j];
            out.flush();
        }
        out << "\n";
        out.flush();
    }

}


