#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    playButtonPlayIcon("../cs372-FinalProject/Button-Play-icon.png"),
    playButtonPauseIcon("../cs372-FinalProject/Button-Pause-icon.png"),
    isPlaying(false)
{
    ui->setupUi(this);

    /*************SETTING UP PLAY BUTTON******************/
    connect(&playButton, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
    playButton.setParent(this);
    playButton.setIcon(playButtonPlayIcon);
    playButton.setGeometry(0,0,90,50);
    playButton.show();
    /*
    connect(&playButton2, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
    playButton2.setParent(this);
    playButton2.setGeometry(playButton.width(),0, playButton.width(), playButton.height());
    playButton2.setIcon(playButtonIcon);
    playButton2.show();*/
}

MainWindow::~MainWindow()
{
    delete ui;
}
