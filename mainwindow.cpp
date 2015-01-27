#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _player(new mediaPlayerTabWidget),
    _controlPanel(new controlPanel)
{
    ui->setupUi(this);

    QWidget * centralWidget = new QWidget;
    QVBoxLayout * centralLayout = new QVBoxLayout;

    if(QCoreApplication::arguments().size())
    {
        QStringList * args = new QStringList(QCoreApplication::arguments());
        args->removeFirst();
        _player->addMedia(args);
    }

    connect(_controlPanel->widget(controlPanel::PlayPauseButton), SIGNAL(clicked()), _player, SLOT(togglePlayPause()));
    connect(_controlPanel->widget(controlPanel::NextButton), SIGNAL(clicked()), _player, SLOT(next()));
    connect(_controlPanel->widget(controlPanel::PreviousButton), SIGNAL(clicked()), _player, SLOT(previous()));
    connect(_controlPanel->widget(controlPanel::VolumeSlider), SIGNAL(sliderMoved(int)), _player, SLOT(setVolume(int)));

    centralLayout->addWidget(_player);
    centralLayout->addWidget(_controlPanel);

    centralWidget->setLayout(centralLayout);

    this->setCentralWidget(centralWidget);
}

MainWindow::~MainWindow()
{
    delete ui;
}
