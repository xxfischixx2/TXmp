#ifndef FMEDIAPLAYER_H
#define FMEDIAPLAYER_H

#include <QObject>

class FMediaPlayer : public QObject
{
    Q_OBJECT
public:
    explicit FMediaPlayer(QObject *parent = 0);

signals:

public slots:
};

#endif // FMEDIAPLAYER_H