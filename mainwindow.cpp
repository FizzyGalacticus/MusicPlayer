#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    /*playButton(this),*/
    playButton2(this),
    playButtonIcon("../cs372-FinalProject/Button-Play-icon.png")
{
    ui->setupUi(this);
    //playButton.setText("Play");
    playButton.setIcon(playButtonIcon);
    playButton.show();
    playButton2.setGeometry(playButton.width(),0, playButton.width(), playButton.height());
    playButton2.setIcon(playButtonIcon);
    playButton2.show();
    connect(&playButton, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
}

MainWindow::~MainWindow()
{
    delete ui;
}
