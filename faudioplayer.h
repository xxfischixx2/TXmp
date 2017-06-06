#ifndef FAUDIOPLAYER_H
#define FAUDIOPLAYER_H

#include <QObject>
#include <QAudioBuffer>
#include <QAudioOutput>
#include <QUrl>
#include <QAudioDecoder>
#include <QFileDevice>


class FAudioPlayer : public QObject
{
    Q_OBJECT

public:

    explicit FAudioPlayer(QObject *parent = 0);

    void test();

signals:



public slots:

    void setMedia(QUrl mediaUrl);

    //void setVolume(int volume);

    void play();

    //void pause();

    //void stop();

private:

    QAudioBuffer *audioBuffer;
    QAudioOutput *audioOutputDevice;
    QAudioDecoder *audioDecoder;
    QUrl *mediaUrl;
    QFileDevice *fileDevice;

};

#endif // FAUDIOPLAYER_H
