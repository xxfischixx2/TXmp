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

    updateSettings();

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

    ui->path->setText(QFileDialog::getExistingDirectory(this, tr("Select Directory"), "C://"));
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

void Settings::on_reset_clicked()
{
    settings->clear();
    updateSettings();
}

void Settings::updateSettings()
{
    ui->autoPlay->setChecked(settings->value("playback/autoPlay", qVariantFromValue(true)).toBool());
    ui->continuePlayingPlaySelected->setChecked(settings->value("playback/continuePlayingPlaySelected", qVariantFromValue(true)).toBool());
    ui->playbackOrder->setCurrentIndex(settings->value("playback/playbackOrder", qVariantFromValue(1)).toInt());

    ui->paths->clear();

    pathlist = settings->value("media/library").toStringList();

    for(int i = 0;i < pathlist.count();i++){

        ui->paths->addItem(pathlist[i]);
    }
}
