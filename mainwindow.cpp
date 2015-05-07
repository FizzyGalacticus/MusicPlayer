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
#include "mediadatabase.h"
#include "user.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow),
    _player(new mediaPlayerTabWidget),
    _videoWidget(new videoWidget),
    _controlPanel(new controlPanel),
    _lyricsBox(new lyricBox),
    _progressBar(new progressBar),
    _menu(new QMenuBar),
    _user(new User),
    _mainWindowIcon(":/resources/icons/mainWindowIcon.png"),
    _previousButtonIcon(":/resources/icons/Button-Prev-icon.png"),
    _nextButtonIcon(":/resources/icons/Button-Next-icon.png"),
    _playButtonIcon(":/resources/icons/Button-Play-icon.png"),
    _pauseButtonIcon(":/resources/icons/Button-Pause-icon.png")
{
    ui->setupUi(this);

    setWindowIcon(_mainWindowIcon);
    setWindowTitle(tr("Music Player"));

    setupPlayer();

    setupLyricsAndControlPanel();

    setWidgetPositions();

    setupMenuBar();

    mediaDatabase * db = new mediaDatabase;
    _player->setMediaDatabase(db);

    _user->setMediaDatabase(db);
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
    centralLayout->setContentsMargins(2,2,2,2);

    centralWidget->setLayout(centralLayout);

    this->setCentralWidget(centralWidget);
}

void MainWindow::setupMenuBar()
{
    //File menu
    QMenu * fileMenu = new QMenu(tr("File"));

    QList<QAction *> fileMenuActions;

    QAction * openMedia = new QAction(tr("Open Media"), this);
    QAction * addMedia = new QAction(tr("Add Media"), this);
    openMedia->setShortcut(QKeySequence("CTRL+O"));
    addMedia->setShortcut(QKeySequence("CTRL+A"));
    connect (openMedia, SIGNAL(triggered()), _player, SLOT(openMedia()));
    connect (addMedia, SIGNAL(triggered()), _player, SLOT(addMedia()));

    fileMenuActions.push_back(addMedia);
    fileMenuActions.push_back(openMedia);

    fileMenu->addActions(fileMenuActions);

    //User menu
    QMenu * userMenu = new QMenu(tr("User"));

    QList<QAction *> userMenuActions;

    QAction * login = new QAction(tr("Login"), this);
    QAction * create = new QAction(tr("Create User"), this);
    login->setShortcut(QKeySequence("CTRL+L"));
    connect(login, SIGNAL(triggered()), _user, SLOT(presentLoginWindow()));
    connect(create, SIGNAL(triggered()), _user, SLOT(presentCreateUserWindow()));

    userMenuActions.push_back(login);
    userMenuActions.push_back(create);

    userMenu->addActions(userMenuActions);

    //Add menus
    _menu->addMenu(fileMenu);
    _menu->addMenu(userMenu);

    this->setMenuBar(_menu);
}
