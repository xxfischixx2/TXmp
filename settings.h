#ifndef SETTINGS_H
#define SETTINGS_H

#include <QDialog>
#include <QStringList>
#include "mainwindow.h"

namespace Ui {
class Settings;
}

class Settings : public QDialog
{
    Q_OBJECT

public:
    explicit Settings(QWidget *parent = 0);
    ~Settings();

    QStringList pathlist;

private slots:

    void on_add_clicked();

    void on_Delete_clicked();

    void on_search_clicked();

    void on_autoPlay_toggled(bool checked);

    void on_playbackOrder_currentIndexChanged(int index);

    void on_continuePlayingPlaySelected_toggled(bool checked);

    void on_reset_clicked();

private:

    void updateSettings();

    Ui::Settings *ui;
    QSettings *settings;

};

#endif // SETTINGS_H
