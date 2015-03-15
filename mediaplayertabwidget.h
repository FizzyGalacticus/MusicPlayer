#ifndef MEDIAPLAYERTABWIDGET_H
#define MEDIAPLAYERTABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include "basePlayer.h"
#include <QLabel>
#include <QList>
#include "controlpanel.h"
#include "lyricbox.h"

class mediaPlayerTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mediaPlayerTabWidget(QWidget *parent = 0);

    bool addMedia(const QStringList *filenames);
    bool openMedia(const QStringList *filenames);
    void setControlPanel(controlPanel *);
    void setLyricBox(lyricBox *);

signals:

public slots:
    void newMetaDataReceived(const QString&artist, const QString &title);
    void togglePlayPause();
    void next();
    void previous();
    void setVolume(int volume);

private slots:
    void playerStateHasChanged(QMediaPlayer::State);

private:
    QTabWidget *_tabs;
    QLabel *_metaData;

    QList<basePlayer *> * _players;
    basePlayer * _currentlyPlayingPlayer;
    controlPanel * _controlPanel;
    lyricBox * _lyricsBox;
};

#endif // MEDIAPLAYERTABWIDGET_H
