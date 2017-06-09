#ifndef FAUDIOPLAYER_H
#define FAUDIOPLAYER_H

#include <QObject>
#include <QAudioBuffer>
#include <QAudioOutput>
#include <QUrl>
#include <QAudioDecoder>
#include <QFile>
#include <QBuffer>


class FAudioPlayer : public QObject
{
    Q_OBJECT

public:

    explicit FAudioPlayer(QObject *parent = 0);

    void setMedia(QUrl mediaUrl);

signals:



public slots:

    //void setVolume(int volume);

    void play();

    //void pause();

    //void stop();

    void on_BufferReady();

private:

    QAudioBuffer *audioBuffer;
    QAudioOutput *audioOutputDevice;
    QAudioDecoder *audioDecoder;
    QUrl *mediaUrl;
    QFile *fileDevice;
    QBuffer *fileBuffer;

};

#endif // FAUDIOPLAYER_H
