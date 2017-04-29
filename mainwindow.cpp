#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "settings.h"
#include <QSettings>
#include <QDirIterator>


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
    time = new QTime;
    settings = new QSettings;

    //UI-Setup

    this->move(settings->value("window/position", qVariantFromValue(QPoint(1000, 1000))).toPoint());
    this->resize(settings->value("window/size", qVariantFromValue(QSize(617, 485))).toSize());

    ui->library->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->library->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->library->setWordWrap(false);
    ui->library->horizontalHeader()->setStretchLastSection(true);
    ui->library->horizontalHeader()->setHighlightSections(false);
    ui->library->verticalHeader()->setVisible(false);

    ui->playlist->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->playlist->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->playlist->setWordWrap(false);
    ui->playlist->horizontalHeader()->setStretchLastSection(true);
    ui->playlist->horizontalHeader()->setHighlightSections(false);
    ui->playlist->verticalHeader()->setVisible(false);
    //ui->playlist->setDragDropMode(QAbstractItemView::InternalMove);

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
    ui->playlist->setRowCount(pList.count());
    player->setVolume(settings->value("playback/volume", qVariantFromValue(100)).toInt());
    ui->volume->setSliderPosition(settings->value("playback/volume", qVariantFromValue(100)).toInt());

    for(int i = 0;i < pList.count();i++){

        fName.setFile(pList[i]);
        playlist->addMedia(QUrl::fromLocalFile(pList[i]));
        ui->playlist->setItem(i, 0, new QTableWidgetItem(fName.fileName()));
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

    for(int i = 0;i < ui->library->rowCount();i++){

        delete ui->library->item(i, 0);
    }

    pathlist = settings->value("media/library").toStringList();
    filters << "*.mp3" << "*.wav" << "*.m4a";

    for(int i = 0;i < pathlist.count();i++){

        QDirIterator mDir(pathlist[i], filters, QDir::NoFilter ,QDirIterator::Subdirectories);

        while(mDir.hasNext()){

            library << mDir.next();
        }

    }

    ui->library->setRowCount(library.count());

    for(int i = 0;i < library.count();i++){

        fName.setFile(library[i]);
        ui->library->setItem(i, 0, new QTableWidgetItem(fName.fileName()));
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

    if(player->mediaStatus() != 1){

        if(player->state() == 2){

            player->play();
        }

        else{

            player->stop();
            player->play();
        }

        fName.setFile(pList[playlist->currentIndex()]);
        this->setWindowTitle("TXmp | " + fName.fileName());
    }

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

    updateLibrary();
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

void MainWindow::on_library_cellDoubleClicked(int row, int column)
{
    QFileInfo fName;

    ui->playlist->setRowCount(ui->playlist->rowCount()+1);
    fName.setFile(library[row]);
    pList << library[row];
    playlist->addMedia(QUrl::fromLocalFile(library[row]));
    ui->playlist->setItem(ui->playlist->rowCount() - 1, 0,new QTableWidgetItem(fName.fileName()));
    settings->setValue("media/playlists/playlist", pList);
}

void MainWindow::on_playlist_cellDoubleClicked(int row, int column)
{
    playlist->setCurrentIndex(row);
    player->play();
}

void MainWindow::on_currentIndexChanged(int position)
{
    if(settings->value("playback/autoPlay", qVariantFromValue(true)).toBool() == false){

        player->stop();
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
    int currentRow = ui->playlist->currentRow();

    playlist->removeMedia(currentRow);
    pList.removeAt(ui->playlist->currentRow());
    delete ui->playlist->currentItem();

    for(int i = currentRow;i < ui->playlist->rowCount();i++){

        if(currentRow != ui->playlist->rowCount() - 1){

            ui->playlist->setItem(i, 0, ui->playlist->takeItem(i + 1, 0));
        }

    }

    ui->playlist->setRowCount(pList.count());
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

    for(int i = 0;i < ui->playlist->rowCount();i++){

        delete ui->playlist->item(i, 0);
    }

    ui->playlist->setRowCount(0);
    pList.clear();
    settings->setValue("media/playlists/playlist", pList);
}
