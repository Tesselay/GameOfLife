#include "mainmenu.h"
#include "playfield.h"
#include "utilities.h"
#include <QString>
#include <QTextStream>
#include <QTime>
#include <QDebug>

MainMenu::MainMenu()
{
    main();
}

void MainMenu::main() {
    QTextStream in(stdin);
    QTextStream out(stdout);

    QString banner = banner_constructor();

    out << banner << "\n";
    out.flush();

    QString user_input {};      // Saved as String to prevent undefined behaviour when entering a string as input
    while (user_input.toInt() != 3) {

        for( int i = 0; i < menu_points.size(); i++ ) {
           out << "\t[" << i+1 << "] " << menu_points.at(i) << "\n";
           out.flush();
        }

        out << "\n> ";
        out.flush();

        in >> user_input;

        Utilities::clear_screen();
        if (user_input.toInt() == 1) {
            out << "Start\n";
            out.flush();

            Playfield playfield;
            QString user_input_start {1};
            while (true) {

                QString test {};
                for ( int i {0}; i < 10; i++) {
                    playfield.field_printer();
                    Utilities::delay(1);
                }



                break;
            }




        }
        else if (user_input.toInt() == 2) {
            out << "Unit Test\n";
            out.flush();
        }
        else if (user_input.toInt() == 3) {
            out << "Bye!";
            out.flush();
            break;
        }
        else {
            out << "Please choose one of the options.\n";
            out.flush();
        }

    }

}

QString MainMenu::banner_constructor() {

    int banner_width {50};
    QString line_body(banner_width, '=');
    QString line {'+' + line_body + '+'};
    QString title {"Game Of Life!"};

    QString banner {line + "\n\t\t" + title + "\n" + line};
    return banner;
}

