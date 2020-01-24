#include "mainmenu.h"
#include "gamelogic.h"
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
            // START
            GameLogic game_logic;
            while (true) {

                for ( int i {0}; i < 20; i++) {
                    game_logic.next_step();
                    Utilities::delay(1);
                    Utilities::clear_screen();
                }
                break;
            }
        }
        else if (user_input.toInt() == 2) {
            // UNIT TEST
        }
        else if (user_input.toInt() == 3) {
            // CLOSE APPLICATION
            out << "Bye!";
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

