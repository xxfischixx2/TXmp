#include "faudioplayer.h"
#include <QAudioBuffer>
#include <QAudioOutput>
#include <QUrl>
#include <QAudioDecoder>
#include <QDebug>
#include <QFileDevice>

FAudioPlayer::FAudioPlayer(QObject *parent) : QObject(parent)
{

    audioBuffer = new QAudioBuffer;
    audioOutputDevice = new QAudioOutput;
    audioDecoder = new QAudioDecoder(this);
    //fileDevice = new QFileDevice;

}

void FAudioPlayer::setMedia(QUrl mediaUrl)
{
    qDebug() << mediaUrl.toString();
    audioDecoder->setSourceFilename(mediaUrl.toString());
}

void FAudioPlayer::play()
{
    QAudioBuffer buff;
    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(2);
    format.setCodec("audio/x-raw");
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::UnSignedInt);

    audioDecoder->setAudioFormat(format);

    qDebug() << audioDecoder->state() << audioDecoder->error();

    audioDecoder->start();

    qDebug() << audioDecoder->state() << audioDecoder->error() << audioDecoder->sourceFilename() << audioDecoder->errorString();

    if(buff.isValid() == true){

        qDebug() <<"dfhhdh";
    }
    if(audioDecoder->bufferAvailable() == true){

        qDebug() << "djbh";
        buff = audioDecoder->read();
    }

}

void FAudioPlayer::test(){


}
