#include "mainwindow.h"
#include <QApplication>
#include <QDir>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    vector<TimeOption> timeOptions;

    timeOptions.push_back(TimeOption("2 sec", 2));
    timeOptions.push_back(TimeOption("10 sec", 10));
    timeOptions.push_back(TimeOption("1 min", 60));
    timeOptions.push_back(TimeOption("2 min", 60*2));
    timeOptions.push_back(TimeOption("3 min", 60*3));
    timeOptions.push_back(TimeOption("4 min", 60*4));
    timeOptions.push_back(TimeOption("5 min", 60*5));
    timeOptions.push_back(TimeOption("7 min", 60*7));
    timeOptions.push_back(TimeOption("10 min", 60*10));
    timeOptions.push_back(TimeOption("15 min", 60*15));
    timeOptions.push_back(TimeOption("20 min", 60*20));
    timeOptions.push_back(TimeOption("30 min", 60*30));
    timeOptions.push_back(TimeOption("45 min", 60*45));
    timeOptions.push_back(TimeOption("1 hour", 60*60));

    MainWindow w(timeOptions);
    w.show();

    return a.exec();
}
