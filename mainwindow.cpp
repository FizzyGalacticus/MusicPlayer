#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _player(new mediaPlayerTabWidget),
    _controlPanel(new controlPanel),
    _mainWindowIcon(":/icons/mainWindowIcon.png"),
    _previousButtonIcon(":/icons/Button-Prev-icon.png"),
    _nextButtonIcon(":/icons/Button-Next-icon.png"),
    _playButtonIcon(":/icons/Button-Play-icon.png"),
    _pauseButtonIcon(":/icons/Button-Pause-icon.png")
{
    ui->setupUi(this);

    QWidget * centralWidget = new QWidget;
    QVBoxLayout * centralLayout = new QVBoxLayout;

    setWindowIcon(_mainWindowIcon);
    setWindowTitle("Music Player");

    if(QCoreApplication::arguments().size())
    {
        QStringList * args = new QStringList(QCoreApplication::arguments());
        args->removeFirst();
        _player->addMedia(args);
    }

    connect(_controlPanel->widget(controlPanel::PlayPauseButton), SIGNAL(clicked()), _player, SLOT(togglePlayPause()));
    connect(_controlPanel->widget(controlPanel::PlayPauseButton), SIGNAL(clicked()), _controlPanel, SLOT(togglePlayPauseState()));
    connect(_controlPanel->widget(controlPanel::NextButton), SIGNAL(clicked()), _player, SLOT(next()));
    connect(_controlPanel->widget(controlPanel::PreviousButton), SIGNAL(clicked()), _player, SLOT(previous()));
    connect(_controlPanel->widget(controlPanel::VolumeSlider), SIGNAL(sliderMoved(int)), _player, SLOT(setVolume(int)));

    _controlPanel->setPlayButtonIcon(_playButtonIcon);
    _controlPanel->setPauseButtonIcon(_pauseButtonIcon);
    _controlPanel->setNextButtonIcon(_nextButtonIcon);
    _controlPanel->setPreviousButtonIcon(_previousButtonIcon);


    centralLayout->addWidget(_player);
    centralLayout->addWidget(_controlPanel);

    centralWidget->setLayout(centralLayout);

    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
