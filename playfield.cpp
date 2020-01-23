#include "playfield.h"
#include <QTextStream>
#include <QDebug>
#include <QProcess>

Playfield::Playfield()
{
    field_constructor();
    init_state();
}

void Playfield::field_constructor() {
    int field_size {25};

    for ( int i {0}; i < field_size; i++) {

        QStringList row {};
        for ( int j {0}; j < field_size; j++) {
            row.append("   ");
        }
        field.append(row);
    }
}

void Playfield::field_printer() {
    QTextStream out(stdout);

    QProcess::execute("cmd /c cls");

    for ( int i {0}; i < field.size(); i++) {

        for ( int j {0}; j < field[0].size(); j++) {

            out << field[i][j];
            out.flush();
        }

        out << "\n";
        out.flush();
    }

}

void Playfield::init_state() {
    int len_x {3};
    int len_y {1};

    int start_pos_x { (field[0].size() / 2) - (len_x / 2)};
    int start_pos_y { (field.size() / 2) - (len_y / 2) };

    for ( int i {0}; i < len_y; i++) {
        for ( int j {0}; j < len_x; j++) {
            field[start_pos_y+i][start_pos_x + j] = " X ";
        }
    }


}
