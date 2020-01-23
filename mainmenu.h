#ifndef MAINMENU_H
#define MAINMENU_H
#include <QString>
#include <QStringList>
#include <vector>

class MainMenu
{
public:
    MainMenu();
    void main();

private:
    QString banner_constructor();
    QStringList menu_points {"Start", "Unit Test", "Close Application"};
};

#endif // MAINMENU_H
