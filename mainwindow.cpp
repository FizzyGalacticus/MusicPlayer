#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QWidget>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QMouseEvent>
#include <QKeyEvent>
#include <QAction>
#include <QList>
#include <QMenu>
#include <QtSql/QSqlDatabase>
#include <QSqlError>
#include <QSqlQuery>
#include <QSqlResult>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _player(new mediaPlayerTabWidget),
    _videoWidget(new videoWidget),
    _controlPanel(new controlPanel),
    _lyricsBox(new lyricBox),
    _progressBar(new progressBar),
    _menu(new QMenuBar),
    _mainWindowIcon(":/icons/mainWindowIcon.png"),
    _previousButtonIcon(":/icons/Button-Prev-icon.png"),
    _nextButtonIcon(":/icons/Button-Next-icon.png"),
    _playButtonIcon(":/icons/Button-Play-icon.png"),
    _pauseButtonIcon(":/icons/Button-Pause-icon.png")
{
    ui->setupUi(this);

    setWindowIcon(_mainWindowIcon);
    setWindowTitle(tr("Music Player"));

    setupPlayer();

    setupLyricsAndControlPanel();

    setWidgetPositions();

    setupMenuBar();

    QSqlDatabase database = QSqlDatabase::addDatabase("QMYSQL");
    database.setHostName("Localhost");
    database.setUserName("root");
    database.setPassword("rootpass");

    bool ok = database.open();

    if(ok)
    {
        qDebug() << "Database opened!";

        QSqlQuery query("CREATE DATABASE IF NOT EXISTS `Foo`;", database);
        query.exec("USE `Test`;");

        while(query.next())
            qDebug() << query.result()->handle().toString();

        database.close();
    }
    else
    {
        qDebug() << "Could not open database!";
        qDebug() << "Error:" << database.lastError().text();
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupPlayer()
{
    if(QCoreApplication::arguments().size())
    {
        QStringList * args = new QStringList(QCoreApplication::arguments());
        args->removeFirst();
        _player->addMedia(args);
    }

    _player->setVideoWidget(_videoWidget);
    _player->setControlPanel(_controlPanel);
    _player->setLyricBox(_lyricsBox);
    _player->setProgressBar(_progressBar);
}

void MainWindow::setupLyricsAndControlPanel()
{
    _lyricsBox->setFont(QFont("Comic Sans MS"));

    _controlPanel->setPlayButtonIcon(_playButtonIcon);
    _controlPanel->setPauseButtonIcon(_pauseButtonIcon);
    _controlPanel->setNextButtonIcon(_nextButtonIcon);
    _controlPanel->setPreviousButtonIcon(_previousButtonIcon);
}

void MainWindow::setWidgetPositions()
{
    QWidget * centralWidget = new QWidget;
    QHBoxLayout * playerAndLyricsLayout = new QHBoxLayout;
    QVBoxLayout * centralLayout = new QVBoxLayout;

    playerAndLyricsLayout->addWidget(_videoWidget);
    playerAndLyricsLayout->addWidget(_player);
    playerAndLyricsLayout->addWidget(_lyricsBox);
    centralLayout->addLayout(playerAndLyricsLayout);
    centralLayout->addWidget(_progressBar);
    centralLayout->addWidget(_controlPanel);

    centralWidget->setLayout(centralLayout);

    this->setCentralWidget(centralWidget);
}

void MainWindow::setupMenuBar()
{
    QAction * openMedia = new QAction(tr("Open Media"), this);
    QAction * addMedia = new QAction(tr("Add Media"), this);
    openMedia->setShortcut(QKeySequence("CTRL+O"));
    addMedia->setShortcut(QKeySequence("CTRL+A"));
    connect (openMedia, SIGNAL(triggered()), _player, SLOT(openMedia()));
    connect (addMedia, SIGNAL(triggered()), _player, SLOT(addMedia()));

    QList<QAction *> actions;

    actions.push_back(addMedia);
    actions.push_back(openMedia);

    QMenu * m = new QMenu(tr("File"));

    m->addActions(actions);

    _menu->addMenu(m);

    this->setMenuBar(_menu);
}