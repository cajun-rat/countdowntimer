#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <iostream>
#include <sstream>
#include <QFontMetrics>
#include <QPainter>
#include <Qtime>
#include <QtDebug>


MainWindow::MainWindow(vector<TimeOption> timeOptions_, QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    timer(this),
    finishedSource(":/sounds/alarm.raw"),
    timeOptions(timeOptions_)
{

    ui->setupUi(this);

    for (vector<TimeOption>::iterator it = timeOptions.begin(); it!= timeOptions.end(); ++ it) {
        TimeOption o = *it;
        ui->timeSelection->addItem(QString::fromStdString(o.name));
    }

    finishedSource.open(QIODevice::ReadOnly);
    QAudioFormat format;
    format.setSampleRate(44100);
    format.setChannelCount(1);
    format.setSampleSize(16);
    format.setCodec("audio/pcm");
    format.setByteOrder(QAudioFormat::LittleEndian);
    format.setSampleType(QAudioFormat::SignedInt);

    QAudioDeviceInfo info(QAudioDeviceInfo::defaultOutputDevice());
    if (!info.isFormatSupported(format)) {
        qWarning() << "Raw audio format not supported by backend, cannot play audio.";
        finishedSound = NULL;
    } else {
        finishedSound = new QAudioOutput(format, this);
        //finishedSound->start(&finishedSource);
    }

    connect(ui->startTimer, SIGNAL(clicked()), this, SLOT(startCountDown()));
    connect(&timer, SIGNAL(timeout()), this, SLOT(timerTick()));
    connect(ui->fullscreen, SIGNAL(clicked()), this, SLOT(fullScreenClicked()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::timerTick() {
    int secondsToGo = QTime::currentTime().secsTo(finishTime);
    ui->timeDisplay->setSecondsRemaining(secondsToGo);
    if (secondsToGo <= 0) {
        if (finishedSound) {
            finishedSource.reset();
            finishedSound->start(&finishedSource);
        }
        timer.stop();
    }
}

void MainWindow::startCountDown() {

    int selectionIndex = ui->timeSelection->currentIndex();
    if (selectionIndex == -1) {
        return;
    }
    int secondsToGo = timeOptions[selectionIndex].seconds;
    finishTime = QTime::currentTime().addSecs(secondsToGo);
    timer.start(1000);
    ui->timeDisplay->setSecondsRemaining(secondsToGo);
}

void MainWindow::fullScreenClicked() {
    if (isFullScreen()) {
        this->setWindowState(Qt::WindowNoState);
    } else {
        this->setWindowState(Qt::WindowFullScreen);
    }
}

void MainWindow::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape && isFullScreen()) {
        this->setWindowState(Qt::WindowNoState);
    }
}


TimeDisplay::TimeDisplay(QWidget *parent) :
    QWidget(parent), m_SecondsToGo(0) {}

void TimeDisplay::paintEvent(QPaintEvent*) {
    stringstream text;
    if (m_SecondsToGo > 0) {
        text << " ";
        text.width(2);
        text << m_SecondsToGo/60;
        text << ":";
        text.width(2);
        text.fill('0');
        text << m_SecondsToGo % 60;
    } else {
        text << "TIME UP";
    }

    QPainter painter(this);
    painter.setRenderHint(QPainter::TextAntialiasing);
    QString t = QString::fromStdString(text.str());

    int points = 34;
    QFont font("Consolas", points);
    QFontMetrics metrics(font, this);
    QRect first = metrics.boundingRect("TIME UP");
    int pointsforwidth = points * width() / first.width();
    int pointsforheight = points * height() / first.height();
    points = min(pointsforwidth, pointsforheight);
    font = QFont("Consolas", points);
    metrics = QFontMetrics(font, this);
    painter.setFont(font);
    painter.setBrush(QBrush(Qt::black));
    QRect second = metrics.boundingRect("TIME UP");
    int x = (width() - second.width())/2;
    int y = (height() + second.height())/2 - metrics.descent();
    painter.drawText(x, y, t);
}

void TimeDisplay::setSecondsRemaining(int seconds) {
    m_SecondsToGo = seconds;
    this->update();
}

