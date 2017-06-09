#include "faudioplayer.h"
#include <QAudioOutput>
#include <QUrl>
#include <QDebug>

FAudioPlayer::FAudioPlayer(QObject *parent) : QObject(parent)
{

    audioBuffer = new QAudioBuffer;
    audioOutputDevice = new QAudioOutput;
    audioDecoder = new QAudioDecoder(this);
    fileDevice = new QFile;
    //fileBuffer = new QBuffer(this);

    fileDevice->open(QIODevice::ReadOnly);

    connect(audioDecoder, &QAudioDecoder::bufferReady, this, &FAudioPlayer::on_BufferReady);
}

void FAudioPlayer::setMedia(QUrl mediaUrl)
{

    fileDevice->setFileName(mediaUrl.toString());
    fileDevice->open(stdin, QIODevice::ReadOnly);
    audioDecoder->setSourceDevice(fileDevice);
}

void FAudioPlayer::play()
{

    QAudioFormat format;
    format.setSampleRate(48000);
    format.setChannelCount(2);
    format.setCodec("audio/pcm");
    format.setSampleSize(16);
    format.setSampleType(QAudioFormat::UnSignedInt);

    audioDecoder->setAudioFormat(format);

    //qDebug() << audioDecoder->state() << audioDecoder->error();

    audioDecoder->start();

    //qDebug() << audioDecoder->state() << audioDecoder->error() << audioDecoder->sourceDevice() << audioDecoder->errorString();
}

void FAudioPlayer::on_BufferReady()
{

    *audioBuffer = audioDecoder->read();

    if(audioBuffer->isValid() == false){

        qDebug() << "error";
    }

    qDebug() << "ldfjbh";

}
