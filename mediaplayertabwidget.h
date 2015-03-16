#ifndef MEDIAPLAYERTABWIDGET_H
#define MEDIAPLAYERTABWIDGET_H

#include <QWidget>
#include <QTabWidget>
#include "basePlayer.h"
#include <QLabel>
#include <QList>
#include "controlpanel.h"
#include "lyricbox.h"
#include "progressbar.h"
#include <QVideoWidget>

class mediaPlayerTabWidget : public QWidget
{
    Q_OBJECT
public:
    explicit mediaPlayerTabWidget(QWidget *parent = 0);

    bool addMedia(const QStringList *filenames);
    bool openMedia(const QStringList *filenames);
    void setVideoWidget(QVideoWidget *);
    void setControlPanel(controlPanel *);
    void setLyricBox(lyricBox *);
    void setProgressBar(progressBar *);

signals:
    void currentPlayerDurationChanged(qint64);
    void currentPlayerPositionChanged(qint64);

public slots:
    void newMetaDataReceived(const QString&artist, const QString &title);
    void togglePlayPause();
    void next();
    void previous();
    void setVolume(int volume);
    void setMediaPosition(int position);

private slots:
    void playerStateHasChanged(QMediaPlayer::State);
    void durationChanged(qint64);
    void positionChanged(qint64);
    void videoAvailableChanged(bool videoAvailable);

private:
    QTabWidget *_tabs;
    QLabel *_metaData;

    QList<basePlayer *> * _players;
    QVideoWidget * _videoWidget;
    basePlayer * _currentlyPlayingPlayer;
    controlPanel * _controlPanel;
    lyricBox * _lyricsBox;
    progressBar * _progressBar;
};

#endif // MEDIAPLAYERTABWIDGET_H
