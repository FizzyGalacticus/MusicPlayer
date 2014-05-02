#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    playButtonIcon("../cs372-FinalProject/Button-Play-icon.png")
{
    ui->setupUi(this);

    /*************SETTING UP PLAY BUTTON******************/
    connect(&playButton, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
    playButton.setParent(this);
    playButton.setIcon(playButtonIcon);
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
