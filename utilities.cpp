#include "utilities.h"
#include <QTime>
#include <QProcess>
#include <QDebug>

Utilities::Utilities()
{

}

void Utilities::delay(int seconds) {
    QTime time(0,0,0);
    time.start();
    QTime stop = time.addSecs(seconds);
    while(time.currentTime() < stop) {
    }
}

void Utilities::clear_screen() {
#ifdef _WIN32
    QProcess::execute("cmd /c cls");
#elif defined __unix__ || defined __linux__ || defined __APPLE__
    QProcess::execute("clear");

#endif
}

QList<QList<int>> Utilities::remove_duplicates(QList<QList<int>> list) {
    std::sort(list.begin(), list.end());
    for ( int i {0}; i < list.size(); i++) {
        while ( list.count(list[i]) > 1 ) {
            list.removeAt(list.indexOf(list[i]));
        }
    }

    return list;

}
