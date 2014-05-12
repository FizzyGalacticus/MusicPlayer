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

    /***********VOLUME SLIDER SLOT***********/
    void _volumeSliderValueChanged();

    /**************MENU OPTION SLOTS****************/
    void open();
    void addMedia();
    void about();
    void aboutQt();
    void aboutAuthors();

    /*************Media Player Slots************/
    void playbackPositionChanged(qint64 position);
    void durationHasChanged(qint64 duration);

    /*************SHUFFLE BUTTON SLOT*********/
    void _shuffleButtonHasBeenPressed();

    /**************PLAYLIST VIEW SLOT**********/
    void playlistItemHasBeenClicked(QListWidgetItem *);
    void resetPlaylistViewFunctionality(QListWidgetItem* item = 0);

    /**************LOOP CHECKBOX SLOT**********/
    void _loopCheckboxStateHasChanged(int);

private:
    Ui::MainWindow *_ui;
    QIcon _mainWindowIcon;
    bool _isPlaying;
    bool _isShuffled;

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
    QMenu *_helpMenu;
    QAction *_openAct;
    QAction *_addMediaAct;
    QAction *_playAct;
    QAction *_nextSongAct;
    QAction *_previousSongAct;
    QAction *_exitAct;
    QAction *_aboutAct;
    QAction *_aboutQtAct;
    QAction *_aboutAuthorsAct;
    QLabel *_infoLabel;

    QIcon _helpIcon, _infoIcon, _openIcon, _exitIcon, _qtIcon;

    /************Volume Slider*******************/
    QLabel *_volumeLabel;
    QSlider *_volumeSlider;

    /************File Name Display**************/
    QLabel * _fileMetadata;

    /***********Media Player*********************/
    QMediaPlayer * _player;
    QMediaPlaylist * _playlist;

    /*************Open file dialogue*************/
    QStringList _openFileDialogue();

    /**************Progress Bar*****************/
    QProgressBar * _progressBar;

    /**************Shuffle Button**************/
    QPushButton *_shuffleButton;

    /**************Playlist View***************/
    QListWidget *_playlistView;
    const QString getAudioInfo(const QMediaContent &) const;
    void refreshPlaylistView();

    /**************Playlist tabs***************/
    QTabWidget * _playlistTabs;

    /**************Loop Checkbox***************/
    QCheckBox * _loopCheckbox;

    /*************SETUP FUNCTIONS***************/
    void setupButtons();
    void setupProgressBar();
    void setupVolumeLabelAndSlider();
    void setupMetadataLabel();
    void setupShuffleButton();
    void setupMenus();
    void setupPlaylistTabs();
    void setupPlaylistView();
    void setupLoopCheckbox();
    void setup();
};

#endif // MAINWINDOW_H
