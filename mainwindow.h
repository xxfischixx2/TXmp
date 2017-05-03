#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include "settings.h"
#include <QStringList>
#include <QDir>
#include <QSettings>
#include <QString>
#include <QTime>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    QStringList library;
    QStringList pathlist;
    QStringList filters;
    QStringList pList;

private slots:

    void on_actionStop_triggered();

    void on_actionPause_triggered();

    void on_actionPlay_triggered();

    void on_actionBack_triggered();

    void on_actionSkip_triggered();

    void on_durationChanged(qint64 position);

    void on_volume_valueChanged(int position);

    void on_progress_sliderReleased();

    void on_actionSettings_triggered();

    void on_positionChanged(qint64 position);

    void on_library_cellDoubleClicked(int row, int column);

    void on_playlist_cellDoubleClicked(int row, int column);

    void on_currentIndexChanged(int position);

    void on_actionDelete_triggered();

    void on_playbackOrder_currentIndexChanged(int index);
    
    void on_actionClear_triggered();

private:

    void updateLibrary();

    void updateTime();

    void updatePlaybackOrder();

    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QTime *time;
    QSettings *settings;
    QAudioFormat format;
};

#endif // MAINWINDOW_H
