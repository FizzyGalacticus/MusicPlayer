#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "mediaplayertabwidget.h"
#include "controlpanel.h"
#include <QIcon>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    mediaPlayerTabWidget * _player;
    controlPanel * _controlPanel;

    //Icons
    QIcon _mainWindowIcon, _previousButtonIcon, _nextButtonIcon, _playButtonIcon,
            _pauseButtonIcon;
};

#endif // MAINWINDOW_H
