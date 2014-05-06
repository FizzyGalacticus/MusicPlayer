#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _mainWindowIcon(":/Resources/icons/mainWindowIcon.jpg"),
    _isPlaying(false),
    _prevButtonIcon(":/Resources/icons/Button-Prev-icon.png"),
    _playButtonPlayIcon(":/Resources/icons/Button-Play-icon.png"),
    _playButtonPauseIcon(":/Resources/icons/Button-Pause-icon.png"),
    _nextButtonIcon(":/Resources/icons/Button-Next-icon.png"),
    _fileMetadata(new QLabel(this)),
    _player(0),
    _playlist(new QMediaPlaylist(this)),
    _progressBar(new QProgressBar(this))
{
    _ui->setupUi(this);
    setWindowIcon(_mainWindowIcon);
    setWindowTitle("Music Player");

    setFixedWidth(8*72);
    setFixedHeight(5*72);

    /****************SETTING UP MENUS*********************/
    QWidget *topFiller = new QWidget;
    topFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

#ifdef Q_OS_SYMBIAN
    _infoLabel = new QLabel(tr("<i>Choose a menu option</i>"));
#else
    _infoLabel = new QLabel(tr("<i>Choose a menu option, or right-click to "
                              "invoke a context menu</i>"));
#endif
    _infoLabel->setFrameStyle(QFrame::StyledPanel | QFrame::Sunken);
    _infoLabel->setAlignment(Qt::AlignCenter);

    QWidget *bottomFiller = new QWidget;
    bottomFiller->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(5);
    layout->addWidget(topFiller);
    layout->addWidget(_infoLabel);
    layout->addWidget(bottomFiller);

    createActions();
    createMenus();

    /************SETTING UP STATUS BAR********************/
#ifndef Q_OS_SYMBIAN
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
#endif

    setupButtons();

    /*************SETTING UP VOLUME SLIDER******************/

    _volumeLabel = new QLabel;
    _volumeLabel->setText(tr("<b>Volume:</b>"));
    _volumeLabel->setParent(this);
    _volumeSlider = new QSlider(Qt::Horizontal);
    _volumeSlider->setParent(this);
    _volumeSlider->setMinimum(0);
    _volumeSlider->setMaximum(100);
    _volumeSlider->setSliderPosition(_volumeSlider->maximum());
    _volumeSlider->setSingleStep(10);
    _volumeSlider->setGeometry
            (
                _nextButton.geometry().x(),
                _playButton.geometry().y()-20,
                _playButton.width(),
                20
            );

    connect(_volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(_volumeSliderValueChanged()));

    /*************SETTING UP VOLUME LABEL******************/
    _volumeLabel->setGeometry
            (
                _volumeSlider->geometry().x()-60,
                _volumeSlider->geometry().y(),
                60,
                _volumeSlider->height()
            );
    _volumeLabel->show();
    _volumeSlider->show();

    /************SETTING UP FILENAME LABEL*********/
    _fileMetadata->setGeometry
            (
                0,
                _volumeLabel->geometry().y(),
                _volumeLabel->geometry().x(),
                _volumeLabel->geometry().height()
            );
    _fileMetadata->show();

    /******************SOUND CODE******************/
    _player = new QMediaPlayer;
    _player->setVolume(100);

    setupProgressBar();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

/***********PLAY BUTTON FUNCTION SLOT***********/
void MainWindow::_playButtonIsPressed ()
{
    _player->pause();

    if(!_isPlaying)
    {
        _playButton.setIcon(_playButtonPauseIcon);
        _player->play();
    }
    else _playButton.setIcon(_playButtonPlayIcon);

    _isPlaying = !_isPlaying;
}

/***********NEXT BUTTON FUNCTION SLOT***********/
void MainWindow::_nextButtonIsPressed ()
{
    _playlist->next();
}

/***********PREV BUTTON FUNCTION SLOT***********/
void MainWindow::_prevButtonIsPressed ()
{
    _playlist->previous();
}

/***********VOLUME SLIDER FUNCTION SLOT***********/
void MainWindow::_volumeSliderValueChanged()
{
        _player->setVolume(_volumeSlider->value());
}

/**************MENU OPTION SLOTS****************/
void MainWindow::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    menu.addAction(_playAct);
    menu.addAction(_nextSongAct);
    menu.addAction(_previousSongAct);
    menu.exec(event->globalPos());
}

void MainWindow::play()
{
    _playButtonIsPressed();
}

void MainWindow::nextSong()
{
    _nextButtonIsPressed();
}

void MainWindow::previousSong()
{
    _prevButtonIsPressed();
}

void MainWindow::open()
{
    QFileDialog openFileDialog(this);
    openFileDialog.setNameFilter(tr("Audio (*.mp3 *.mp4 *.wav *.flac *.ogg)"));
    openFileDialog.setViewMode(QFileDialog::List);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);
    openFileDialog.setDirectory("../cs372-FinalProject/");

    QStringList fileNames;
    if(openFileDialog.exec())
       fileNames = openFileDialog.selectedFiles();

    QList<QMediaContent> playListFiles;

    for(QStringList::iterator file = fileNames.begin(); file < fileNames.end(); file++)
       playListFiles.append(QMediaContent(QUrl::fromLocalFile(*file)));

    _playlist->clear();
    _playlist->addMedia(playListFiles);
    _playlist->setPlaybackMode(QMediaPlaylist::Loop);
    _player->stop();
    _player->setPlaylist(_playlist);
    _player->setPosition(0);

    if(_isPlaying) _playButtonIsPressed();
}

void MainWindow::about()
{
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about(this, tr("About Menu"),
            tr("Hit Play to Play Mooxzikz. "
               "Open to Open More Moozikz."));
//TODO: docoomentimgz
}

void MainWindow::aboutQt()
{
    _infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::createActions()
{
    _openAct = new QAction(tr("&Open..."), this);
    _openAct->setStatusTip(tr("Open an existing file"));
    connect(_openAct, SIGNAL(triggered()), this, SLOT(open()));

    _exitAct = new QAction(tr("E&xit"), this);
    _exitAct->setStatusTip(tr("Exit the application"));
    connect(_exitAct, SIGNAL(triggered()), this, SLOT(close()));

    _playAct = new QAction(tr("&Play/Pause"), this);
    _playAct->setStatusTip(tr("Play a song"));
    connect(_playAct, SIGNAL(triggered()), this, SLOT(play()));

    _nextSongAct = new QAction(tr("&Next Song"), this);
    _nextSongAct->setStatusTip(tr("Switches to the Next Song"));
    connect(_nextSongAct, SIGNAL(triggered()), this, SLOT(nextSong()));

    _previousSongAct = new QAction(tr("&Previous Song"), this);
    _previousSongAct->setStatusTip(tr("Switches to the Previous Song"));
    connect(_previousSongAct, SIGNAL(triggered()), this, SLOT(previousSong()));

    _aboutAct = new QAction(tr("&About"), this);
    _aboutAct->setStatusTip(tr("Show the application's About box"));
    connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    _aboutQtAct = new QAction(tr("About &Qt"), this);
    _aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    connect(_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(_aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));
}

void MainWindow::createMenus()
{
    _fileMenu = menuBar()->addMenu(tr("&File"));
    _fileMenu->addAction(_openAct);
    _fileMenu->addSeparator();
    _fileMenu->addAction(_exitAct);

    _playMenu = menuBar()->addMenu(tr("&Play"));
    _playMenu->addSeparator();
    _playMenu->addAction(_playAct);
    _playMenu->addAction(_nextSongAct);
    _playMenu->addAction(_previousSongAct);

    _helpMenu = menuBar()->addMenu(tr("&Help"));
    _helpMenu->addAction(_aboutAct);
    _helpMenu->addAction(_aboutQtAct);
}

void MainWindow::setupButtons()
{
    const int mediaButtonYCoordinate =
            (
                height()- ((width()/5) + statusBar()->geometry().height() - 8)
            );

    //Setup signals
    connect(&_prevButton, SIGNAL(clicked()), this, SLOT(_prevButtonIsPressed()));
    connect(&_playButton, SIGNAL(clicked()), this, SLOT(_playButtonIsPressed()));
    connect(&_nextButton, SIGNAL(clicked()), this, SLOT(_nextButtonIsPressed()));

    //Setup parents
    _prevButton.setParent(this);
    _playButton.setParent(this);
    _nextButton.setParent(this);

    //Setup positions
    _prevButton.setGeometry
            (
                0,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    _playButton.setGeometry
            (
                _prevButton.width()*2,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    _nextButton.setGeometry
            (
                _playButton.width()*4,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );

    //Setup icons
    _prevButton.setIcon(_prevButtonIcon);
    _prevButton.setIconSize(QSize(_prevButton.height(),_prevButton.height()));

    _playButton.setIcon(_playButtonPlayIcon);
    _playButton.setIconSize(QSize(_playButton.height(),_playButton.height()));

    _nextButton.setIcon(_nextButtonIcon);
    _nextButton.setIconSize(QSize(_nextButton.height(),_nextButton.height()));

    //Show them off
    _prevButton.show();
    _playButton.show();
    _nextButton.show();
}

void MainWindow::playbackPositionChanged(qint64 position)
{
    _progressBar->setValue(position);
}

void MainWindow::durationHasChanged(qint64 duration)
{
    _fileMetadata->setText
            (
                //_player->currentMedia().canonicalUrl().fileName()
                _player->metaData("AlbumArtist").toString() + " - " +
                _player->metaData("Title").toString()
            );
    _progressBar->setRange(0,duration);
}

void MainWindow::setupProgressBar()
{
    _progressBar->setGeometry(0,28,width(),height()/3);
    _progressBar->setValue(0);
    connect(_player, SIGNAL(positionChanged(qint64)), this, SLOT(playbackPositionChanged(qint64)));
    connect(_player, SIGNAL(durationChanged(qint64)),this, SLOT(durationHasChanged(qint64)));
    _progressBar->show();
}
