#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    mainWindowIcon(":/Resources/icons/mainWindowIcon.jpg"),
    isPlaying(false),
    prevButtonIcon(":/Resources/icons/Button-Prev-icon.png"),
    playButtonPlayIcon(":/Resources/icons/Button-Play-icon.png"),
    playButtonPauseIcon(":/Resources/icons/Button-Pause-icon.png"),
    nextButtonIcon(":/Resources/icons/Button-Next-icon.png"),
    _player(0),
    _playlist(this)
{
    ui->setupUi(this);
    setWindowIcon(mainWindowIcon);
    setWindowTitle("Music Player");

    setFixedWidth(5*72);
    setFixedHeight(3*72);

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

    /************SETTING UP STATUS BAR********************/
#ifndef Q_OS_SYMBIAN
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
#endif

    /*****************SETTING UP BUTTONS******************/
    const int mediaButtonYCoordinate =
            (
                (height() + layout->geometry().height())-
                ((width()/5) + statusBar()->geometry().height() - 8)
            );
    /*************SETTING UP PREV BUTTON******************/
    connect(&prevButton, SIGNAL(clicked()), this, SLOT(prevButtonIsPressed()));
    prevButton.setParent(this);
    prevButton.setGeometry
            (
                0,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    prevButton.setIcon(prevButtonIcon);
    prevButton.setIconSize(QSize(prevButton.height(),prevButton.height()));
    prevButton.show();

    /*************SETTING UP PLAY BUTTON******************/
    connect(&playButton, SIGNAL(clicked()), this, SLOT(playButtonIsPressed()));
    playButton.setParent(this);
    playButton.setGeometry
            (
                prevButton.width()*2,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    playButton.setIcon(playButtonPlayIcon);
    playButton.setIconSize(QSize(playButton.height(),playButton.height()));
    playButton.show();

    /*************SETTING UP NEXT BUTTON******************/
    connect(&nextButton, SIGNAL(clicked()), this, SLOT(nextButtonIsPressed()));
    nextButton.setParent(this);
    nextButton.setGeometry
            (
                playButton.width()*4,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    nextButton.setIcon(nextButtonIcon);
    nextButton.setIconSize(QSize(nextButton.height(),nextButton.height()));
    nextButton.show();

    /*************SETTING UP VOLUME SLIDER******************/

    volumeLabel = new QLabel;
    volumeLabel->setText(tr("<b>Volume:</b>"));
    volumeLabel->setParent(this);
    volumeSlider = new QSlider(Qt::Horizontal);
    volumeSlider->setParent(this);
    volumeSlider->setMinimum(0);
    volumeSlider->setMaximum(100);
    volumeSlider->setSingleStep(10);
    volumeSlider->setGeometry
            (
                nextButton.geometry().x(),
                mediaButtonYCoordinate-20,
                playButton.width(),
                20
            );
    volumeLabel->setGeometry
            (
                volumeSlider->geometry().x()-60,
                volumeSlider->geometry().y(),
                60,
                volumeSlider->height()
            );
    volumeLabel->show();
    volumeSlider->show();

    /******************SOUND CODE******************/
    _player = new QMediaPlayer;
    _player->setMedia(QUrl::fromLocalFile("/home/dustin/CS/MusicPlayer/cs372-FinalProject/test.mp3"));
    _player->setVolume(100);

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
   QFileDialog openFileDialog(this);
   openFileDialog.setNameFilter(tr("Audio (*.mp3 *.mp4 *.wav *.flac *.ogg)"));
   openFileDialog.setViewMode(QFileDialog::List);
   openFileDialog.setFileMode(QFileDialog::ExistingFiles);

   QStringList fileNames;
   if(openFileDialog.exec())
       fileNames = openFileDialog.selectedFiles();

   QList<QMediaContent> playListFiles;

   for(QStringList::iterator file = fileNames.begin(); file < fileNames.end(); file++)
       playListFiles.append(QMediaContent(QUrl::fromLocalFile(*file)));

   _playlist.clear();
   _playlist.addMedia(playListFiles);
   _player->stop();
   _player->setPlaylist(&_playlist);
   _player->setPosition(1);
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
    playAct->setStatusTip(tr("Play a song"));
    connect(playAct, SIGNAL(triggered()), this, SLOT(play()));

    nextSongAct = new QAction(tr("&Next Song"), this);
    nextSongAct->setStatusTip(tr("Switches to the Next Song"));
    connect(nextSongAct, SIGNAL(triggered()), this, SLOT(nextSong()));

    previousSongAct = new QAction(tr("&Previous Song"), this);
    previousSongAct->setStatusTip(tr("Switches to the Previous Song"));
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

