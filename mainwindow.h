#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QKeyEvent>
#include <QMainWindow>
#include <QTimer>
#include <QTime>
#include <qtmultimedia/QAudioOutput>
#include <vector>
#include <string>

using namespace std;

namespace Ui {
class MainWindow;
struct TimeOption;
}


struct TimeOption {
    string name;
    int seconds;
public:
    TimeOption(string name_, int seconds_) : name(name_), seconds(seconds_) { }
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
private:
    Ui::MainWindow *ui;
    vector<TimeOption> timeOptions;
    QTime finishTime;
    QTimer timer;
    QFile finishedSource;
    QAudioOutput *finishedSound;

public slots:
    void startCountDown();
    void timerTick();
    void fullScreenClicked();
    void keyPressEvent(QKeyEvent *event);
};

class TimeDisplay : public QWidget
{
    Q_OBJECT

public:
    TimeDisplay(QWidget *parent=0);
    void setSecondsRemaining(int seconds);
protected:
    void paintEvent(QPaintEvent *event);
private:
    int m_SecondsToGo;
};


#endif // MAINWINDOW_H
