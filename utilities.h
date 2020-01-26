#ifndef UTILITIES_H
#define UTILITIES_H
#include <QList>
#include <QTime>
#include <QProcess>

class Utilities
{
public:
    Utilities();
    static void delay(int seconds);
    static void clear_screen();
    static QList<QList<int>> remove_duplicates(QList<QList<int>> list);

};

#endif // UTILITIES_H
