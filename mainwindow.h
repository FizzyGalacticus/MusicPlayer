#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QPushButton>
#include <QIcon>

class QAction;
class QActionGroup;
class QLabel;
class QMenu;

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
        if(!isPlaying) playButton.setIcon(playButtonPauseIcon);
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
};

#endif // MAINWINDOW_H
