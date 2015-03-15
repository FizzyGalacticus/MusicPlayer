#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _player(new mediaPlayerTabWidget),
    _controlPanel(new controlPanel),
    _lyricsBox(new lyricBox),
    _mainWindowIcon(":/icons/mainWindowIcon.png"),
    _previousButtonIcon(":/icons/Button-Prev-icon.png"),
    _nextButtonIcon(":/icons/Button-Next-icon.png"),
    _playButtonIcon(":/icons/Button-Play-icon.png"),
    _pauseButtonIcon(":/icons/Button-Pause-icon.png")
{
    ui->setupUi(this);

    QWidget * centralWidget = new QWidget;
    QHBoxLayout * playerAndLyricsLayout = new QHBoxLayout;
    QVBoxLayout * centralLayout = new QVBoxLayout;

    setWindowIcon(_mainWindowIcon);
    setWindowTitle("Music Player");

    if(QCoreApplication::arguments().size())
    {
        QStringList * args = new QStringList(QCoreApplication::arguments());
        args->removeFirst();
        _player->addMedia(args);
    }

    _player->setControlPanel(_controlPanel);
    _player->setLyricBox(_lyricsBox);

    _controlPanel->setPlayButtonIcon(_playButtonIcon);
    _controlPanel->setPauseButtonIcon(_pauseButtonIcon);
    _controlPanel->setNextButtonIcon(_nextButtonIcon);
    _controlPanel->setPreviousButtonIcon(_previousButtonIcon);

    playerAndLyricsLayout->addWidget(_player);
    playerAndLyricsLayout->addWidget(_lyricsBox);
    centralLayout->addLayout(playerAndLyricsLayout);
    centralLayout->addWidget(_controlPanel);

    centralWidget->setLayout(centralLayout);

    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
