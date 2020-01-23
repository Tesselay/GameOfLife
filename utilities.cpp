#include "utilities.h"
#include <QTime>
#include <QProcess>

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
#elif defined __unix__ || defined __linux__ || __APPLE__
    QProcess::execute("clear");

#endif
}
