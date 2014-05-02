#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainWindowIcon("../cs372-FinalProject/icons/mainWindowIcon.jpg"),
    playButtonPlayIcon("../cs372-FinalProject/icons/Button-Play-icon.png"),
    playButtonPauseIcon("../cs372-FinalProject/icons/Button-Pause-icon.png"),
    nextButtonIcon("../cs372-FinalProject/icons/Button-Next-icon.png"),
    prevButtonIcon("../cs372-FinalProject/icons/Button-Prev-icon.png"),
    isPlaying(false)
{
    ui->setupUi(this);
    setWindowIcon(mainWindowIcon);

    /*************SETTING UP PREV BUTTON******************/
    connect(&prevButton, SIGNAL(clicked()), this, SLOT(prevButtonIsPressed()));
    prevButton.setParent(this);
    prevButton.setIcon(prevButtonIcon);
    prevButton.setGeometry(0,0,90,50);
    prevButton.show();

    /*************SETTING UP PLAY BUTTON******************/
    connect(&playButton, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
    playButton.setParent(this);
    playButton.setIcon(playButtonPlayIcon);
    playButton.setGeometry(prevButton.width(),0,prevButton.width(),prevButton.height());
    playButton.show();

    /*************SETTING UP NEXT BUTTON******************/
    connect(&nextButton, SIGNAL(clicked()), this, SLOT(nextButtonIsPressed()));
    nextButton.setParent(this);
    nextButton.setIcon(nextButtonIcon);
    nextButton.setGeometry(playButton.width()+prevButton.width(),0,prevButton.width(),prevButton.height());
    nextButton.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
