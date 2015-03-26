#ifndef BASEPLAYER_H
#define BASEPLAYER_H

#include <QWidget>
#include <QListWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QString>
#include "videowidget.h"
#include "mediadatabase.h"

class basePlayer : public QWidget
{
    Q_OBJECT
public:
    explicit basePlayer(QWidget *parent = 0);

    bool openMedia(const QMediaContent & content);
    bool openMedia(const QList<QMediaContent> & items);
    bool addMedia(const QMediaContent & content);
    bool addMedia(const QList<QMediaContent> & items);
    static const QList<QMediaContent> * getMediaContentFromFilePaths(const QStringList *);
    void setVideoWidget(videoWidget *);
    void setMediaDatabase(mediaDatabase * db);
    bool clear();
    QStringList * openFileDialog();
    const QString & artist() const;
    const QString & album() const;
    const QString & title() const;

signals:
    void stateChanged(QMediaPlayer::State state);
    void metaDataChanged(const QString &artist, const QString &title);
    void durationChanged(qint64 duration);
    void positionChanged(qint64 position);
    void videoAvailabilityChanged(bool videoAvailable);

public slots:
    void togglePlayPause();
    void next();
    void previous();
    void setVolume(int volume);
    void setMediaPosition(qint64);

private slots:
    void currentIndexHasChanged(int index);
    void metaDataChanged();
    void metaDataAvailablityHasChanged(bool isMetaDataAvailable);
    void initiateAddMedia();
    void initiateOpenMedia();
    void mediaDurationChanged(qint64);
    void mediaPositionChanged(qint64);
    void videoAvailableChanged(bool videoAvailable);
    void mediaStateChanged(QMediaPlayer::State state);

protected:
    bool event(QEvent *);

private:
    QListWidget * _basePlayerView;
    QMediaPlayer * _player;
    QMediaPlaylist * _mediaPlaylist;
    mediaDatabase * _db;

    QString _currentlyPlayingArtist;
    QString _currentlyPlayingAlbum;
    QString _currentlyPlayingTitle;

    void removeFeaturingArtistFromTitle();
    const QString * getAudioFileTypes();
};

#endif // PLAYLIST_H
