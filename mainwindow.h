#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>
#include <QLabel>
#include <QSlider>
#include <QtMultimedia/QMediaPlayer>

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

private slots:
    /***********PLAY BUTTON FUNCTION SLOT***********/
    void playButtonIsPressed ()
    {
        _player->pause();

        if(!isPlaying)
        {
            playButton.setIcon(playButtonPauseIcon);
            _player->play();
        }
        else playButton.setIcon(playButtonPlayIcon);

        isPlaying = !isPlaying;
    }

    /***********NEXT BUTTON FUNCTION SLOT***********/
    void nextButtonIsPressed ()
    {
        //Go to next song
    }

    /***********PREV BUTTON FUNCTION SLOT***********/
    void prevButtonIsPressed ()
    {
        //Go to previous song
    }

    void open();
    void play();
    void nextSong();
    void previousSong();
    void about();
    void aboutQt();

private:
    Ui::MainWindow *ui;
    QIcon mainWindowIcon;
    bool isPlaying;

    /************Prev Button Objects*************/
    QPushButton prevButton;
    QIcon prevButtonIcon;

    /************Play Button Objects*************/
    QPushButton playButton;
    QIcon playButtonPlayIcon, playButtonPauseIcon;

    /************Next Button Objects*************/
    QPushButton nextButton;
    QIcon nextButtonIcon;

    /**************Menu Objects and Functions***/
    void createActions();
    void createMenus();

    QMenu *fileMenu;
    QMenu *playMenu;
    QMenu *helpMenu;
    QAction *openAct;
    QAction *playAct;
    QAction *nextSongAct;
    QAction *previousSongAct;
    QAction *exitAct;
    QAction *aboutAct;
    QAction *aboutQtAct;
    QLabel *infoLabel;

    /************Volume Slider*******************/
    QLabel *volumeLabel;
    QSlider *volumeSlider;

    /***********Media Player*********************/
    QMediaPlayer * _player;
};

#endif // MAINWINDOW_H
