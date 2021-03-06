#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtMultimedia>
#include "settings.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_actionStop_triggered();

    void on_actionPause_triggered();

    void on_actionPlay_triggered();

    void on_durationChanged(qint64 position);

    void on_volume_valueChanged(int position);

    void on_progress_sliderReleased();

    void on_actionSettings_triggered();

    void on_positionChanged(qint64 position);

    void on_libraryTable_cellDoubleClicked(int row, int column);

    void on_playlistTable_cellDoubleClicked(int row, int column);

    void on_currentIndexChanged(int position);

    void on_actionDelete_triggered();

    void on_playbackOrder_currentIndexChanged(int index);
    
    void on_actionClear_triggered();

    void on_actionAbout_triggered();

    void on_actionUpdateLibrary_triggered();

    void on_searchBar_textEdited(const QString &arg1);

    void on_actionFadeOut_triggered();

    void on_actionFadeIn_triggered();

    void on_actionSkip_triggered();

    void on_actionBack_triggered();

private:

    void updateLibrary();

    void updateTime();

    void updatePlaybackOrder();

    Ui::MainWindow *ui;
    QMediaPlayer *player;
    QMediaPlaylist *playlist;
    QSettings *settings;
    QStringList library;
    QStringList pathlist;
    QStringList filters;
    QStringList pList;
};

#endif // MAINWINDOW_H
