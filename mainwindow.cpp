#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include <QSettings>
#include <QDirIterator>
#include <QUrl>
#include <QDebug>
#include <QtMultimedia>
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    Settings sets;
    sets.setModal(true);

    QCoreApplication::setOrganizationName("TechniX");
    QCoreApplication::setApplicationName("TXmp");
    QFileInfo fName;
    player = new QMediaPlayer(this);
    playlist = new QMediaPlaylist(this);
    settings = new QSettings;

    //UI-Setup

    this->move(settings->value("window/position", qVariantFromValue(QPoint(20, 20))).toPoint());
    this->resize(settings->value("window/size", qVariantFromValue(QSize(617, 485))).toSize());

    ui->libraryTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->libraryTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->libraryTable->setWordWrap(false);
    ui->libraryTable->horizontalHeader()->setStretchLastSection(true);
    ui->libraryTable->horizontalHeader()->setHighlightSections(false);
    ui->libraryTable->verticalHeader()->setVisible(false);

    ui->playlistTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlistTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlistTable->setWordWrap(false);
    ui->playlistTable->horizontalHeader()->setStretchLastSection(true);
    ui->playlistTable->horizontalHeader()->setHighlightSections(false);
    ui->playlistTable->verticalHeader()->setVisible(false);
    //ui->playlistTable->setDragDropMode(QAbstractItemView::InternalMove);

    ui->playbackOrder->setCurrentIndex(settings->value("playback/playbackOrder", qVariantFromValue(1)).toInt());

    //Signals and Slots

    connect(player, &QMediaPlayer::positionChanged, this, &MainWindow::on_positionChanged);
    connect(player, &QMediaPlayer::durationChanged, this, &MainWindow::on_durationChanged);
    connect(playlist, &QMediaPlaylist::currentIndexChanged, this, &MainWindow::on_currentIndexChanged);

    //Library-Setup

    updateLibrary();

    //Player-Setup

    player->setPlaylist(playlist);
    pList = settings->value("media/playlists/playlist").toStringList();
    ui->playlistTable->setRowCount(pList.count());
    player->setVolume(settings->value("playback/volume", qVariantFromValue(100)).toInt());
    ui->volume->setSliderPosition(settings->value("playback/volume", qVariantFromValue(100)).toInt());

    for(int i = 0;i < pList.count();i++){

        fName.setFile(pList[i]);
        playlist->addMedia(QUrl::fromLocalFile(pList[i]));
        ui->playlistTable->setItem(i, 0, new QTableWidgetItem(fName.fileName()));
    }

    updatePlaybackOrder();

}

MainWindow::~MainWindow()
{
    settings->setValue("window/position", this->pos());
    settings->setValue("window/size", this->size());

    delete ui;
}

void MainWindow::updateLibrary()
{
    QFileInfo fName;

    library.clear();

    for(int i = 0;i < ui->libraryTable->rowCount();i++){

        delete ui->libraryTable->item(i, 0);
    }

    pathlist = settings->value("media/library").toStringList();
    filters << "*.mp3" << "*.wav" << "*.m4a";

    for(int i = 0;i < pathlist.count();i++){

        QDirIterator mDir(pathlist[i], filters, QDir::NoFilter ,QDirIterator::Subdirectories);

        while(mDir.hasNext()){

            library << mDir.next();
        }

    }

    ui->libraryTable->setRowCount(library.count());

    for(int i = 0;i < library.count();i++){

        fName.setFile(library[i]);
        ui->libraryTable->setItem(i, 0, new QTableWidgetItem(fName.fileName()));
    }

}

void MainWindow::updatePlaybackOrder()
{
    int order = settings->value("playback/playbackOrder", qVariantFromValue(1)).toInt();

    if(order == 0){

        playlist->setPlaybackMode(QMediaPlaylist::CurrentItemInLoop);
    }

    else if(order == 1){

        playlist->setPlaybackMode(QMediaPlaylist::Sequential);
    }

    else if(order == 2){

        playlist->setPlaybackMode(QMediaPlaylist::Loop);
    }

    else if(order == 3){

        playlist->setPlaybackMode(QMediaPlaylist::Random);
    }

}

void MainWindow::updateTime()
{
    qint64 totalMin = player->duration() / 1000 / 60;
    qint64 totalSec = (player->duration() / 1000) - (totalMin * 60);
    qint64 playedMin = player->position() / 1000 / 60;
    qint64 playedSec = (player->position() / 1000) - (playedMin * 60);

    QString sTotalMin = "";
    QString sTotalSec = "";
    QString sPlayedMin = "";
    QString sPlayedSec = "";

    sTotalMin.setNum(totalMin);
    sTotalSec.setNum(totalSec);
    sPlayedMin.setNum(playedMin);
    sPlayedSec.setNum(playedSec);

    if(sTotalSec.count() == 1){

        ui->total->setText(sTotalMin + ":0" + sTotalSec);
    }

    else{

        ui->total->setText(sTotalMin + ":" + sTotalSec);
    }

    if(sPlayedSec.count() == 1){

        ui->played->setText(sPlayedMin + ":0" + sPlayedSec);
    }

    else{

        ui->played->setText(sPlayedMin + ":" + sPlayedSec);
    }
    
}

void MainWindow::on_actionStop_triggered()
{
    player->stop();
    this->setWindowTitle("TXmp");
}

void MainWindow::on_actionPause_triggered()
{
    if(player->state() == 1){

        player->pause();
    }

    else if(player->state() == 2){

        player->play();
    }

}

void MainWindow::on_actionPlay_triggered()
{
    QFileInfo fName;

       if(player->state() == 2 && settings->value("playback/continuePlayingPlaySelected", qVariantFromValue(true)).toBool() == true){

            player->play();
        }

        else{

            playlist->setCurrentIndex(ui->playlistTable->currentRow());
            player->play();
        }

        fName.setFile(pList[playlist->currentIndex()]);
        this->setWindowTitle("TXmp | " + fName.fileName());

}

void MainWindow::on_actionBack_triggered()
{
    playlist->previous();
}

void MainWindow::on_actionSkip_triggered()
{
    playlist->next();
}

void MainWindow::on_durationChanged(qint64 position)
{
    ui->progress->setMaximum(position);

    updateTime();
}

void MainWindow::on_volume_valueChanged(int position)
{
    QSettings settings;

    player->setVolume(position);
    settings.setValue("playback/volume", position);
}

void MainWindow::on_progress_sliderReleased()
{
    int position = 0;

    position = ui->progress->sliderPosition();
    player->setPosition(position);
}

void MainWindow::on_actionSettings_triggered()
{
    Settings sets;

    sets.setModal(true);
    sets.exec();

    if(settings->value("media/library").toStringList() != pathlist){
        updateLibrary();
    }

    updatePlaybackOrder();
    ui->playbackOrder->setCurrentIndex(settings->value("playback/playbackOrder", qVariantFromValue(1)).toInt());

}

void MainWindow::on_positionChanged(qint64 position)
{
    if(ui->progress->isSliderDown() == false){

        ui->progress->setValue(position);
    }

    updateTime();
}

void MainWindow::on_libraryTable_cellDoubleClicked(int row, int column)
{
    QFileInfo fName;

    ui->playlistTable->setRowCount(ui->playlistTable->rowCount()+1);
    fName.setFile(library[row]);
    pList << library[row];
    playlist->addMedia(QUrl::fromLocalFile(library[row]));
    ui->playlistTable->setItem(ui->playlistTable->rowCount() - 1, 0,new QTableWidgetItem(fName.fileName()));
    settings->setValue("media/playlists/playlist", pList);
}

void MainWindow::on_playlistTable_cellDoubleClicked(int row, int column)
{
    playlist->setCurrentIndex(row);
    player->play();
}

void MainWindow::on_currentIndexChanged(int position)
{
    if(settings->value("playback/autoPlay", qVariantFromValue(true)).toBool() == false){

        player->pause();
    }

    if(position == -1){

        this->setWindowTitle("TXmp");
    }

    else{

        QFileInfo fName;

        fName.setFile(pList[position]);
        this->setWindowTitle("TXmp | " + fName.fileName());
    }

    updateTime();

}

void MainWindow::on_actionDelete_triggered()
{
    int currentRow = ui->playlistTable->currentRow();

    playlist->removeMedia(currentRow);
    pList.removeAt(ui->playlistTable->currentRow());
    delete ui->playlistTable->currentItem();

    for(int i = currentRow;i < ui->playlistTable->rowCount();i++){

        if(currentRow != ui->playlistTable->rowCount() - 1){

            ui->playlistTable->setItem(i, 0, ui->playlistTable->takeItem(i + 1, 0));
        }

    }

    ui->playlistTable->setRowCount(pList.count());
    settings->setValue("media/playlists/playlist", pList);
}

void MainWindow::on_playbackOrder_currentIndexChanged(int index)
{
    settings->setValue("playback/playbackOrder", index);
    updatePlaybackOrder();
}

void MainWindow::on_actionClear_triggered()
{
    playlist->clear();

    for(int i = 0;i < ui->playlistTable->rowCount();i++){

        delete ui->playlistTable->item(i, 0);
    }

    ui->playlistTable->setRowCount(0);
    pList.clear();
    settings->setValue("media/playlists/playlist", pList);
}

void MainWindow::on_actionAbout_triggered()
{
    //QMessageBox::about(this, "About TechniX media player", "<b>TXmp v1.0 Beta</b> <br>Released on: 21.06.2017 <br>Written by Maximilian Fischer for CSG TechniX");

    QMessageBox aboutTXmp;

    aboutTXmp.addButton(QMessageBox::Close);
    aboutTXmp.setDefaultButton(QMessageBox::Close);
    aboutTXmp.setText("<b>TXmp v1.0 Beta</b> <br>Released on: 21.06.2017 <br>Written by Maximilian Fischer for CSG TechniX");
    aboutTXmp.setWindowTitle("About TechniX media player");
    aboutTXmp.exec();
}
