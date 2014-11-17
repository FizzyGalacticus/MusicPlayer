#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QSlider>
#include <QtMultimedia/QMediaPlayer>
#include <QMediaPlaylist>
#include <QFileDialog>
#include <QStringList>
#include <QList>
#include <QProgressBar>
#include <QCheckBox>
#include <QListWidget>
#include <QTabWidget>
#include <QKeyEvent>
#include <QCheckBox>
#include <QWidget>
#include <QVBoxLayout>
#include <QVector>
#include <QDockWidget>
#include <QTextEdit>
#include <QNetworkAccessManager>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;
class QMediaPlayer;

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

protected:
        void contextMenuEvent(QContextMenuEvent *event);
        void keyPressEvent(QKeyEvent *);

private slots:
    /***********BUTTON SLOTS***********/
    void _playButtonIsPressed ();

    void _nextButtonIsPressed ();

    void _prevButtonIsPressed ();

    void _newPlaylistTabButtonIsPressed();

    /***********VOLUME SLIDER SLOT***********/
    void _volumeSliderValueChanged();

    /**************MENU OPTION SLOTS****************/
    void menuOpen();
    void menuAddMedia();
    void about();
    void aboutQt();
    void aboutAuthors();
    bool savePlaylist();
    bool loadPlaylist();
    void menuToggleLyricsBox();

    /*************Media Player Slots************/
    void playbackPositionChanged(qint64 position);
    void durationHasChanged(qint64 duration);
    void playerError(QMediaPlayer::Error);

    /*************SHUFFLE BUTTON SLOT*********/
    void _shuffleButtonHasBeenPressed();

    /**************PLAYLIST VIEW SLOT**********/
    void playlistItemHasBeenClicked(QListWidgetItem *);
    void resetPlaylistViewFunctionality(QListWidgetItem* item = 0);

    /**************LOOP CHECKBOX SLOT**********/
    void _loopCheckboxStateHasChanged(int);

    /*************PLAYLIST TABS SLOTS*************/
    void _tabCloseRequested(int);
    void _currentTabIndexHasChanged(int);

    /*************RETRIEVE LYRICS PAGE************/
    void _lyricsRetrieved(QNetworkReply*);

private:
    Ui::MainWindow *_ui;
    QIcon _mainWindowIcon;
    QWidget * _centralWidget;
    QVBoxLayout * _mainLayout;

    bool _isPlaying;
    bool _isShuffled;

    /*************Network Manager****************/
    QNetworkAccessManager * _networkManager;

    /************Prev Button Objects*************/
    QPushButton *_prevButton;
    QIcon _prevButtonIcon;

    /************Play Button Objects*************/
    QPushButton *_playButton;
    QIcon _playButtonPlayIcon, _playButtonPauseIcon;

    /************Next Button Objects*************/
    QPushButton *_nextButton;
    QIcon _nextButtonIcon;

    /**************Menu Objects and Functions***/
    void createActions();
    void createMenus();

    QMenu *_fileMenu;
    QMenu *_playMenu;
    QMenu *_optionsMenu;
    QMenu *_helpMenu;
    QAction *_openAct;
    QAction *_addMediaAct;
    QAction *_playAct;
    QAction *_nextSongAct;
    QAction *_previousSongAct;
    QAction *_exitAct;
    QAction *_savePlaylistAct;
    QAction *_loadPlaylistAct;
    QAction *_toggleLyricsBox;
    QAction *_aboutAct;
    QAction *_aboutQtAct;
    QAction *_aboutAuthorsAct;
    QLabel *_infoLabel;

    QIcon _helpIcon, _infoIcon, _openIcon, _exitIcon, _qtIcon;

    /************Volume Slider*******************/
    QLabel *_volumeLabel;
    QSlider *_volumeSlider;

    /************Metadata Display****************/
    QLabel * _fileMetadata;

    /***********Media Player*********************/
    QVector<QMediaPlayer *> * _players;
    QMediaPlayer * _currentPlayer;

    /*************Get Audio Files*************/
    void addMedia(const QStringList * media);
    void openMedia(const QStringList * media);
    QString * _defaultMusicDirectory;
    const QString * getAudioFileTypes();
    QStringList * _openFileDialog(const QString *,const QString *);

    /**************Progress Bar*****************/
    QProgressBar * _progressBar;

    /**************Shuffle Button**************/
    QPushButton *_shuffleButton;

    /**************Playlist View***************/
    QVector<QListWidget *> * _playlistViews;
    QListWidget * _currentPlaylistView;
    void setupPlaylistViewConnections(const QListWidget *);
    const QString getAudioInfo(const int &);
    void refreshPlaylistView();

    /**************Playlist tabs***************/
    QTabWidget * _playlistTabs;
    QPushButton * _newPlaylistTabButton;

    /**************Loop Checkbox***************/
    QCheckBox * _loopCheckbox;

    /*************Setup Functions***************/
    void setupButtons();
    void setupProgressBar();
    void setupMetadataLabel();
    void setupMenus();
    void setupPlaylistTabs();
    void setupOptionDash();
    void setupLyricsWidget();
    void setup();

    /*************SQLite Functions**************/
    bool savePlaylist(const int &);
    bool writePlaylist(const QFile *, const int &);
    const QStringList * readPlaylist(const QFile *);
    bool loadPlaylist(const int &);

    /*************Get & Display Lyrics**********/
    void formatLyricsUrlString(QString &);
    void updateSongLyrics(QString, QString);
    QTextEdit * _lyricsTextBox;
    QDockWidget * _lyricsWidget;

    /********ADD ALL MUSIC TO PLAYLIST*********/
    QStringList * getAllMusicFiles(const QString& searchDirectory);
};

#endif // MAINWINDOW_H
