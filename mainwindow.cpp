#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QtWidgets>


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
    prevButton.setGeometry(0,20,90,50);
    prevButton.show();

    /*************SETTING UP PLAY BUTTON******************/
    connect(&playButton, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
    playButton.setParent(this);
    playButton.setIcon(playButtonPlayIcon);
    playButton.setGeometry(prevButton.width(),20,prevButton.width(),prevButton.height());
    playButton.show();

    /*************SETTING UP NEXT BUTTON******************/
    connect(&nextButton, SIGNAL(clicked()), this, SLOT(nextButtonIsPressed()));
    nextButton.setParent(this);
    nextButton.setIcon(nextButtonIcon);
    nextButton.setGeometry(playButton.width()+prevButton.width(),20,prevButton.width(),prevButton.height());
    nextButton.show();


    /****************SETTING UP MENUS*********************/
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

#ifdef Q_OS_SYMBIAN
    infoLabel = new QLabel(tr("<i>Choose a menu option</i>"));
#else
    infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
#endif
    infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(infoLabel);
    layout->addWidget(bottomFiller);

    createActions();
    createMenus();

#ifndef Q_OS_SYMBIAN
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
#endif

    setWindowTitle(tr("Menus"));
    setMinimumSize(160, 160);
    resize(480, 320);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(playAct);
    menu.addAction(nextSongAct);
    menu.addAction(previousSongAct);
    menu.exec(event->globalPos());
}

void MainWindow::play()
{
    playButtonIsPressed();
}

void MainWindow::nextSong()
{
    nextButtonIsPressed();
}

void MainWindow::previousSong()
{
    prevButtonIsPressed();
}

void MainWindow::open()
{
   //TODO: ADD OPEN FUNCTIONALITY
}

void MainWindow::about()
{
    infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("Hit Play to Play Mooxzikz. "
               "Open to Open More Moozikz."));
//TODO: docoomentimgz
}

void MainWindow::aboutQt()
{
    infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::createActions()
{
    openAct = new QAction(tr("&Open..."), this);
    openAct->setStatusTip(tr("Open an existing file"));
    connect(openAct, SIGNAL(triggered()), this, SLOT(open()));

    exitAct = new QAction(tr("E&xit"), this);
    exitAct->setStatusTip(tr("Exit the application"));
    connect(exitAct, SIGNAL(triggered()), this, SLOT(close()));

    playAct = new QAction(tr("&Play/Pause"), this);
    playAct->setStatusTip(tr("Play the last operation"));
    connect(playAct, SIGNAL(triggered()), this, SLOT(play()));

    nextSongAct = new QAction(tr("&Next Song"), this);
    nextSongAct->setStatusTip(tr("Play the last operation"));
    connect(nextSongAct, SIGNAL(triggered()), this, SLOT(nextSong()));

    previousSongAct = new QAction(tr("&Previous Song"), this);
    previousSongAct->setStatusTip(tr("Play the last operation"));
    connect(previousSongAct, SIGNAL(triggered()), this, SLOT(previousSong()));

    aboutAct = new QAction(tr("&About"), this);
    aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    aboutQtAct = new QAction(tr("About &Qt"), this);
    aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    fileMenu = menuBar()->addMenu(tr("&File"));
    fileMenu->addAction(openAct);
    fileMenu->addSeparator();
    fileMenu->addAction(exitAct);

    playMenu = menuBar()->addMenu(tr("&Play"));
    playMenu->addSeparator();
    playMenu->addAction(playAct);
    playMenu->addAction(nextSongAct);
    playMenu->addAction(previousSongAct);

    helpMenu = menuBar()->addMenu(tr("&Help"));
    helpMenu->addAction(aboutAct);
    helpMenu->addAction(aboutQtAct);
}

