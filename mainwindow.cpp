#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QObject>
#include <QtWidgets>


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    _ui(new Ui::MainWindow),
    _mainWindowIcon(":/Resources/icons/mainWindowIcon.png"),
    _isPlaying(false),
    _isShuffled(false),
    _prevButton(new QPushButton(this)),
    _playButton(new QPushButton(this)),
    _nextButton(new QPushButton(this)),
    _prevButtonIcon(":/Resources/icons/Button-Prev-icon.png"),
    _playButtonPlayIcon(":/Resources/icons/Button-Play-icon.png"),
    _playButtonPauseIcon(":/Resources/icons/Button-Pause-icon.png"),
    _nextButtonIcon(":/Resources/icons/Button-Next-icon.png"),
    _helpIcon(":/Resources/icons/Menu-Help-icon.png"),
    _infoIcon(":/Resources/icons/Menu-Info-icon.png"),
    _openIcon(":/Resources/icons/Menu-Open-icon.png"),
    _exitIcon(":/Resources/icons/Menu-Exit-icon.png"),
    _qtIcon(":/Resources/icons/Qt-icon.ico"),
    _volumeLabel(new QLabel(this)),
    _volumeSlider(new QSlider(Qt::Horizontal, this)),
    _fileMetadata(new QLabel(this)),
    _player(new QMediaPlayer(this)),
    _playlist(new QMediaPlaylist(this)),
    _progressBar(new QProgressBar(this)),
    _shuffleCheckbox(new QCheckBox("Shuffle", this))
{
    //_ui->setupUi(this); //I don't think we really need this... but leaving this line here in case
    setWindowIcon(_mainWindowIcon);
    setWindowTitle("Music Player");

    setFixedWidth(7*72);
    setFixedHeight(4*72);

    /****************SETTING UP STATUS BAR*********************/
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

    /****************SETTING UP MENUS*********************/
    createActions();
    createMenus();

    /************SETTING UP STATUS BAR********************/
#ifndef Q_OS_SYMBIAN
    QString message = tr("A context menu is available by right-clicking");
    statusBar()->showMessage(message);
#endif

    _player->setVolume(50);

    setupButtons();
    setupProgressBar();
    setupVolumeLabelAndSlider();
    setupShuffleCheckbox();
    setupMetadataLabel();
}

MainWindow::~MainWindow()
{
    delete _ui;
}

/***********PLAY BUTTON FUNCTION SLOT***********/
void MainWindow::_playButtonIsPressed ()
{
    if(!_playlist->isEmpty())
    {
        if(!_isPlaying)
        {
            _playButton->setIcon(_playButtonPauseIcon);
            _playAct->setIcon(_playButtonPauseIcon);
            _player->play();
        }
        else
        {
            _playButton->setIcon(_playButtonPlayIcon);
            _playAct->setIcon(_playButtonPlayIcon);
            _player->pause();
        }

        _isPlaying = !_isPlaying;
    }
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
    openFileDialog.setNameFilter
            (
                tr
                (
                    "Audio (*.mp3 *.mp4 *.wav *.flac *.ogg *.aiff *.wma *.mid *.ra *.ram *.rm *.vox *.raw *.aac *.au)"
                )
            );
    openFileDialog.setViewMode(QFileDialog::List);
    openFileDialog.setFileMode(QFileDialog::ExistingFiles);

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
            tr("CS 372 - Software Construction"
               "<p>Final Project - \"Music Player\""
               "<p>Spring Semester 2014"));
}

void MainWindow::aboutQt()
{
    _infoLabel->setText(tr("Invoked <b>Help|About Qt</b>"));
}

void MainWindow::aboutAuthors()
{
    _infoLabel->setText(tr("Invoked <b>Help|About</b>"));
    QMessageBox::about
            (
                this,
                tr("Authors Menu"),
                tr
                (
                    "<b><center>Authors:</center></b>"
                    "<p>Dustin Dodson"
                    "<p>Erik Talvi"
                    "<p>Matthew Parrish"
                    "<p>Nate Helms"
                    "<p>Nicholas Mardeusz"
                    "<p>Thomas Cerny"
                )
            );
}

void MainWindow::createActions()
{
    _openAct = new QAction(tr("&Open..."), this);
    _openAct->setStatusTip(tr("Open an existing file"));
    _openAct->setIcon(_openIcon);
    connect(_openAct, SIGNAL(triggered()), this, SLOT(open()));

    _exitAct = new QAction(tr("&Exit"), this);
    _exitAct->setStatusTip(tr("Exit the application"));
    _exitAct->setIcon(_exitIcon);
    connect(_exitAct, SIGNAL(triggered()), this, SLOT(close()));

    _playAct = new QAction(tr("&Play/Pause"), this);
    _playAct->setStatusTip(tr("Play a song"));
    _playAct->setIcon(_playButtonPlayIcon);
    connect(_playAct, SIGNAL(triggered()), this, SLOT(play()));

    _nextSongAct = new QAction(tr("&Next Song"), this);
    _nextSongAct->setStatusTip(tr("Switches to the Next Song"));
    _nextSongAct->setIcon(_nextButtonIcon);
    connect(_nextSongAct, SIGNAL(triggered()), this, SLOT(nextSong()));

    _previousSongAct = new QAction(tr("&Previous Song"), this);
    _previousSongAct->setStatusTip(tr("Switches to the Previous Song"));
    _previousSongAct->setIcon(_prevButtonIcon);
    connect(_previousSongAct, SIGNAL(triggered()), this, SLOT(previousSong()));

    _aboutAct = new QAction(tr("&About"), this);
    _aboutAct->setStatusTip(tr("Show the application's About box"));
    _aboutAct->setIcon(_helpIcon);
    connect(_aboutAct, SIGNAL(triggered()), this, SLOT(about()));

    _aboutQtAct = new QAction(tr("About &Qt"), this);
    _aboutQtAct->setStatusTip(tr("Show the Qt library's About box"));
    _aboutQtAct->setIcon(_qtIcon);
    connect(_aboutQtAct, SIGNAL(triggered()), qApp, SLOT(aboutQt()));
    connect(_aboutQtAct, SIGNAL(triggered()), this, SLOT(aboutQt()));

    _aboutAuthorsAct = new QAction(tr("About &Authors"), this);
    _aboutAuthorsAct->setStatusTip(tr("Show information about Music Player's authors"));
    _aboutAuthorsAct->setIcon(_infoIcon);
    connect(_aboutAuthorsAct, SIGNAL(triggered()),this, SLOT(aboutAuthors()));
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
    _helpMenu->addAction(_aboutAuthorsAct);
}

void MainWindow::setupButtons()
{
    const int mediaButtonYCoordinate =
            (
                height()- ((width()/5) + statusBar()->geometry().height() - 8)
            );

    //Setup signals
    connect(_prevButton, SIGNAL(clicked()), this, SLOT(_prevButtonIsPressed()));
    connect(_playButton, SIGNAL(clicked()), this, SLOT(_playButtonIsPressed()));
    connect(_nextButton, SIGNAL(clicked()), this, SLOT(_nextButtonIsPressed()));

    //Setup positions
    _prevButton->setGeometry
            (
                0,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    _playButton->setGeometry
            (
                _prevButton->width()*2,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );
    _nextButton->setGeometry
            (
                _playButton->width()*4,
                mediaButtonYCoordinate,
                width()/5,
                width()/5
            );

    //Setup icons
    _prevButton->setIcon(_prevButtonIcon);
    _prevButton->setIconSize(QSize(_prevButton->height(),_prevButton->height()));

    _playButton->setIcon(_playButtonPlayIcon);
    _playButton->setIconSize(QSize(_playButton->height(),_playButton->height()));

    _nextButton->setIcon(_nextButtonIcon);
    _nextButton->setIconSize(QSize(_nextButton->height(),_nextButton->height()));

    //Show them off
    _prevButton->show();
    _playButton->show();
    _nextButton->show();
}

void MainWindow::playbackPositionChanged(qint64 position)
{
    _progressBar->setValue(position);
}

void MainWindow::durationHasChanged(qint64 duration)
{
    QString labelStr;

    if(_player->availableMetaData().contains("Title"))
    {
        QString songTitle = _player->metaData("Title").toString();
        if(_player->availableMetaData().contains("AlbumArtist"))
            labelStr =
                    (
                        _player->metaData("AlbumArtist").toString() + " - " +
                        songTitle
                    );
        else labelStr = songTitle;
    }
    else labelStr = _player->currentMedia().canonicalUrl().fileName();

    _fileMetadata->setText(labelStr);
    _progressBar->setRange(0,duration);
}

void MainWindow::shuffleCheckboxHasChanged(int state)
{
    if(state) _playlist->shuffle();
}

void MainWindow::setupProgressBar()
{
    _progressBar->setGeometry(0,28,width(),height()/3);
    _progressBar->setValue(0);
    connect(_player, SIGNAL(positionChanged(qint64)), this, SLOT(playbackPositionChanged(qint64)));
    connect(_player, SIGNAL(durationChanged(qint64)),this, SLOT(durationHasChanged(qint64)));
    _progressBar->show();
}

void MainWindow::setupVolumeLabelAndSlider()
{
    _volumeLabel->setText(tr("<b>Volume:</b>"));
    _volumeSlider->setRange(0,100);
    _volumeSlider->setSliderPosition(_player->volume());
    _volumeSlider->setGeometry
            (
                _nextButton->geometry().x(),
                _playButton->geometry().y()-20,
                _playButton->width(),
                20
            );
    _volumeLabel->setGeometry
            (
                _volumeSlider->geometry().x()-60,
                _volumeSlider->geometry().y(),
                60,
                _volumeSlider->height()
            );

    connect(_volumeSlider,SIGNAL(valueChanged(int)),this,SLOT(_volumeSliderValueChanged()));

    _volumeLabel->show();
    _volumeSlider->show();
}

void MainWindow::setupShuffleCheckbox()
{
    connect(_shuffleCheckbox, SIGNAL(stateChanged(int)), this, SLOT(shuffleCheckboxHasChanged(int)));

    _shuffleCheckbox->setGeometry
            (
                _playButton->geometry().x(),
                _volumeLabel->geometry().y(),
                _volumeSlider->width()+10,
                _volumeLabel->height()
            );

    _shuffleCheckbox->show();
}

void MainWindow::setupMetadataLabel()
{
    _fileMetadata->setGeometry
            (
                0,
                _volumeLabel->geometry().y(),
                _shuffleCheckbox->geometry().x(),
                _volumeLabel->geometry().height()
            );

    _fileMetadata->show();
}
