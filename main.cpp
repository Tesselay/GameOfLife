#include <QCoreApplication>
#include "mainmenu.h"


using namespace std;

int main(int argc, char *argv[])
{
    QCoreApplication a(argc, argv);

    MainMenu main_menu;

    return a.exec();
}
