#ifndef BASEPLAYER_H
#define BASEPLAYER_H

#include <QWidget>
#include <QListWidget>
#include <QtMultimedia/QMediaPlayer>
#include <QtMultimedia/QMediaPlaylist>
#include <QString>

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

signals:
    void stateChanged(QMediaPlayer::State state);
    void metaDataChanged(const QString &artist, const QString &title);

public slots:
    void togglePlayPause();
    void next();
    void previous();
    void setVolume(int volume);

private slots:
    void currentIndexHasChanged(int index);
    void metaDataAvailablityHasChanged(bool isMetaDataAvailable);
    void initiateAddMedia();
    void initiateOpenMedia();

private:
    QListWidget * _basePlayerView;
    QMediaPlayer * _player;
    QMediaPlaylist * _mediaPlaylist;

    QString _currentlyPlayingArtist;
    QString _currentlyPlayingTitle;

    bool clear();
    void removeFeaturingArtistFromTitle();
    const QString * getAudioFileTypes();
    QStringList * openFileDialog();
};

#endif // PLAYLIST_H
