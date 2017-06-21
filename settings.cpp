#include "settings.h"
#include "ui_settings.h"
#include <QFileDialog>
#include <QDebug>
#include <QSettings>
#include "mainwindow.h"

Settings::Settings(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Settings)
{
    ui->setupUi(this);
    settings = new QSettings;

    pathlist = settings->value("media/library").toStringList();

    for(int i = 0;i < pathlist.count();i++){

        ui->paths->addItem(pathlist[i]);
    }

    ui->autoPlay->setChecked(settings->value("playback/autoPlay", qVariantFromValue(true)).toBool());
    ui->continuePlayingPlaySelected->setChecked(settings->value("playback/continuePlayingPlaySelected", qVariantFromValue(true)).toBool());
    ui->playbackOrder->setCurrentIndex(settings->value("playback/playbackOrder", qVariantFromValue(1)).toInt());
}


Settings::~Settings()
{
    delete ui;
}

void Settings::on_add_clicked()
{
    QString path;

    path = ui->path->text();
    ui->paths->addItem(path);
    pathlist.append(path);
    settings->setValue("media/library", pathlist);
    ui->path->clear();
}

void Settings::on_Delete_clicked()
{
    pathlist.removeAt(ui->paths->currentRow());
    settings->setValue("media/library", pathlist);
    delete ui->paths->currentItem();
}

void Settings::on_search_clicked()
{
    QString path = "";

    path = QFileDialog::getExistingDirectory(this, tr("Select Directory"), "C://");
    pathlist.append(path);
    settings->setValue("media/library", pathlist);
    ui->paths->addItem(path);
}

void Settings::on_autoPlay_toggled(bool checked)
{
    settings->setValue("playback/autoPlay", checked);
}

void Settings::on_playbackOrder_currentIndexChanged(int index)
{
    settings->setValue("playback/playbackOrder", index);
}

void Settings::on_continuePlayingPlaySelected_toggled(bool checked)
{
    settings->setValue("playback/continuePlayingPlaySelected", checked);
}
