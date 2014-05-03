#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainWindowIcon(":/Resources/icons/mainWindowIcon.jpg"),
    playButtonPlayIcon(":/Resources/icons/Button-Play-icon.png"),
    playButtonPauseIcon(":/Resources/icons/Button-Pause-icon.png"),
    nextButtonIcon(":/Resources/icons/Button-Next-icon.png"),
    prevButtonIcon(":/Resources/icons/Button-Prev-icon.png"),
    isPlaying(false)
{
    ui->setupUi(this);
    setWindowIcon(mainWindowIcon);

    /*************SETTING UP PREV BUTTON******************/
    connect(&prevButton, SIGNAL(clicked()), this, SLOT(prevButtonIsPressed()));
    prevButton.setParent(this);
    prevButton.setIcon(prevButtonIcon);
    prevButton.setGeometry(0,(2*72)-50,(4*72/3),50);
    prevButton.show();

    /*************SETTING UP PLAY BUTTON******************/
    connect(&playButton, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
    playButton.setParent(this);
    playButton.setIcon(playButtonPlayIcon);
    playButton.setGeometry(prevButton.width(),(2*72)-50,prevButton.width(),prevButton.height());
    playButton.show();

    /*************SETTING UP NEXT BUTTON******************/
    connect(&nextButton, SIGNAL(clicked()), this, SLOT(nextButtonIsPressed()));
    nextButton.setParent(this);
    nextButton.setIcon(nextButtonIcon);
    nextButton.setGeometry(playButton.width()+prevButton.width(),(2*72)-50,prevButton.width(),prevButton.height());
    nextButton.show();
}

MainWindow::~MainWindow()
{
    delete ui;
}
