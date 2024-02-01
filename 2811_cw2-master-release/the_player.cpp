//
// Created by twak on 11/11/2019.
//


#include "the_player.h"
#include "QMouseEvent"
#include <QString>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <QFileDialog>
#include <QMessageBox>
#include <QMediaMetaData>


// Time in milliseconds to skip forwards/backwards.
#define SKIP_TIME 10000

// Get the first video ready to play.
void ThePlayer::setContent() {
    jumpTo(buttons.at(0)->info);
}

void ThePlayer::playStateChanged (QMediaPlayer::State ms) {
    switch (ms) {
        case QMediaPlayer::State::PlayingState:
            playPauseButton->setIcon(pauseIcon);
            break;
        case QMediaPlayer::State::StoppedState:
            play(); // starting playing again...
        default:
            playPauseButton->setIcon(playIcon);
            break;
    }
}

void ThePlayer::jumpTo (TheButtonInfo* button) {
    setMedia( * button -> url);
    play();
    playStateChanged(QMediaPlayer::PlayingState);
}

void ThePlayer::playPause() {
    switch(state()) {
    case QMediaPlayer::PlayingState:
        // std::cout << "Playing, so paused" << std::endl;
        pause();
        break;
    default:
        // std::cout << "Paused, so playing" << std::endl;
        play();
        break;
    }
}

void ThePlayer::skipForward() {
    auto point = position()+SKIP_TIME;
    if (point > duration()) point = duration();
    setPosition(point);
}

void ThePlayer::skipFrameForward() {
    qreal framerate = metaData(QMediaMetaData::VideoFrameRate).toReal();
    if (framerate <= 0) {
        qDebug() << "Framerate not available, assuming 30" << Qt::endl;
        framerate = 30;
    }
    qreal frameTime = qreal(1000)/framerate;
    auto point = position() + frameTime;
    if (point > duration()) point = duration();
    setPosition(point);
}

void ThePlayer::positionChanged(qint64 x) {
    videoSlider->update();
    videoSlider->setValue(x);
}

void ThePlayer::durationChanged(qint64 x) {
    videoSlider->setMaximum(x);
    videoLength = durationToString(duration());
}

void ThePlayer::skipBackward() {
    auto point = position()-SKIP_TIME;
    if (point < 0) point = 0;
    setPosition(point);
}

void ThePlayer::skipFrameBackward() {
    qreal framerate = metaData(QMediaMetaData::VideoFrameRate).toReal();
    if (framerate <= 0) {
        qDebug() << "Framerate not available, assuming 30" << Qt::endl;
        framerate = 30;
    }
    qreal frameTime = qreal(1000)/framerate;
    auto point = position() - frameTime;
    if (point < 0) point = 0;
    setPosition(point);
}

void ThePlayer::connectSlider(int x) {
    setPosition(x);
}

void ThePlayer::languageChanged(QStringList lang) {
    speedString = lang[9];
    changeSpeed(passedPlaybackRate);
    playPauseButton->setToolTip(lang[12] + " (" + QKeySequence(SHORTCUT_PLAYPAUSE).toString() + ")");
    skipForwardButton->setToolTip(lang[13] + " (" + QKeySequence(SHORTCUT_FF).toString() + ")");
    skipBackwardButton->setToolTip(lang[14] + " (" + QKeySequence(SHORTCUT_RW).toString() + ")");
    skipFrameForwardButton->setToolTip(lang[13] + " 1 frame (" + QKeySequence(SHORTCUT_FF_FRAME).toString() + ")");
    skipFrameBackwardButton->setToolTip(lang[14] + " 1 frame (" + QKeySequence(SHORTCUT_RW_FRAME).toString() + ")");
}

// For the speed/slowmo button, clicking it toggles between 1x/0.5x.
void ThePlayer::slowMo() {
    if(playbackRate() == 1){
        setPlaybackRate(0.5);
        passedPlaybackRate = 50;
        speedSlider->setValue(50);
    }
    else{
        setPlaybackRate(1);
        passedPlaybackRate = 100;
        speedSlider->setValue(100);
    }
}

// For the speed slider.
void ThePlayer::changeSpeed(int x) {
    passedPlaybackRate = x;
    setNotifyInterval(1000);
    if (x <= 35){
        setPlaybackRate(0.25);
        speedSlider->setValue(25);
        slowMoButton->setText(speedString + " (25%)");
    }
    else if (x > 35 && x <= 60){
        setPlaybackRate(0.5);
        speedSlider->setValue(50);
        slowMoButton->setText(speedString + " (50%)");
    }
    else if (x > 60 && x <= 85){
        setPlaybackRate(0.75);
        speedSlider->setValue(75);
        slowMoButton->setText(speedString + " (75%)");
    }
    else if (x > 85 && x <= 110){
        setPlaybackRate(1);
        speedSlider->setValue(100);
        slowMoButton->setText(speedString + " (100%)");
    }
    else if (x > 110 && x <= 135){
        setPlaybackRate(1.25);
        speedSlider->setValue(125);
        setNotifyInterval((1.0f/1.25f)*1000);
        slowMoButton->setText(speedString + " (125%)");
    }
    else if (x > 135 && x <= 160){
        setPlaybackRate(1.5);
        speedSlider->setValue(150);
        setNotifyInterval((1.0f/1.5f)*1000);
        slowMoButton->setText(speedString + " (150%)");
    }
    else if (x > 160 && x <= 185){
        setPlaybackRate(1.75);
        speedSlider->setValue(175);
        setNotifyInterval((1.0f/1.75f)*1000);
        slowMoButton->setText(speedString + " (175%)");
    }
    else {
        setPlaybackRate(2);
        speedSlider->setValue(200);
        setNotifyInterval((1.0f/2.0f)*1000);
        slowMoButton->setText(speedString + " (200%)");
    }
}

// Returns a formatted string of the given duration in msec.
QString ThePlayer::durationToString(qint64 x) const {
    // round up to nearest second
    int sec = int(round(double(x)/1000.0f));
    int hour = sec / 3600;
    sec -= 3600*hour;
    int min = sec / 60;
    sec -= 60*min;
    std::ostringstream s;
    if (hour > 0)
        s << std::setw(2) << std::setfill('0') << hour << ':';
    s << std::setw(2) << std::setfill('0') << min << ':';
    s << std::setw(2) << std::setfill('0') << sec;
    QString out = QString::fromStdString(s.str());
    return out;
}

void ThePlayer::positionText(qint64 x) {
    playerPosition->setText(durationToString(x) + "/" + videoLength);
}

void ThePlayer::sliderPositionChanged(int x) {
    positionText(x);
}

/* Checks if the given file is a video, and if so adds it to the stores its information.
 * Also searches for <name>.png thumbnail files, and adds them if found. */
void ThePlayer::addVideoFile(QString f) {
    if (f.contains(".")) {
#if defined(_WIN32)
        if (f.contains(".wmv"))  { // windows
#else
        if (f.contains(".mp4") || f.contains("MOV"))  { // mac/linux
#endif
            qDebug() << "Reading file" << f << Qt::endl;
            QString thumb = f.left( f .length() - 4) +".png";
            QIcon *ico = missingThumb;
            auto width = missingThumbImage.width();
            auto height = missingThumbImage.height();
            if (QFile(thumb).exists()) { // if a png thumbnail exists
                QImageReader *imageReader = new QImageReader(thumb);
                QImage sprite = imageReader->read(); // read the thumbnail
                if (!sprite.isNull()) {
                    ico = new QIcon(QPixmap::fromImage(sprite)); // voodoo to create an icon for the button
                    width = sprite.width();
                    height = sprite.height();
                } else {
                    qDebug() << "warning: thumbnail " << thumb << " was invalid, using placeholder" << Qt::endl;
                }
            } else {
                qDebug() << "warning: couldn't find thumbnail " << thumb << " so using placeholder" << Qt::endl;
            }
            QUrl* url = new QUrl(QUrl::fromLocalFile( f )); // convert the file location to a generic url
            infos.push_back(TheButtonInfo(url, ico, QFileInfo(f), double(width)/double(height))); // add to the output list
        }
    }
}

/* Read video files/thumbnails from given directory/filepath.
 * If clear is true, other videos are erased from memory first.
 * If isFile is true, loc is treated as a video filepath rather than a folder. */
int ThePlayer::getDirInfo (std::string loc, bool clear, bool isFile) {
    if (clear)
        infos.clear();

    if (isFile) {
        addVideoFile(QString::fromStdString(loc));
    } else {
        QDir dir(QString::fromStdString(loc));
        QDirIterator it(dir);

        while (it.hasNext()) { // for all files

            QString f = it.next();
            addVideoFile(f);
        }
    }
    return infos.size();
}

/* Generates and places the buttons for each video.
 * If clear is true, old ones are deleted first. */
void ThePlayer::generateVideoButtons(QWidget *videoButtonsWidget, bool clear) {
    if (buttonWidget == NULL)
        buttonWidget = videoButtonsWidget;

    if (clear) {
        QLayoutItem *videoButton;
        while ((videoButton = layout->takeAt(0)) != 0) {
            videoButton->widget()->deleteLater();
            delete videoButton;
        }
        buttons.clear();
    }
    for ( int i = 0; i < infos.size(); i++ ) {
        TheButton *button = new TheButton(buttonWidget, window);
        button->connect(button, SIGNAL(jumpTo(TheButtonInfo* )), this, SLOT (jumpTo(TheButtonInfo*))); // when clicked, tell the player to play.
        buttons.push_back(button);
        layout->addWidget(button);
        button->init(&(infos.at(i)));
    }
    layout->update();
    if (buttonWidget != NULL) {
        buttonWidget->updateGeometry();
    }
    emit requestRedraw();
}

/* Sets the video directory to default to if an invalid choice
 * is made in the filepicker (unless the filepicker is set to loop). */
void ThePlayer::setDefaultDir(std::string loc) { defaultDir = loc; }

/* Opens the filepicker to select one or more video files.
 * If loop is true, an invalid choice will prompt the user to pick again.
 * If loop is false, the selection will default to videos in defaultDir. */
void ThePlayer::openFile(bool loop) {
    QFileDialog *dialog = new QFileDialog();
    dialog->setFileMode(QFileDialog::ExistingFiles);
    dialog->setNameFilter("Video files (*.MOV, *.wmv, *.mp4)");
    auto success = dialog->exec();
    int count = 0;
    if (success) {
        QStringList fnames = dialog->selectedFiles();
        for (const auto& fname : fnames) {
            count += getDirInfo(fname.toStdString(), count == 0 ? true : false, true);
        }
    }
    if (count == 0) {
        const int result = QMessageBox::information(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! Make sure you selected the right ones."));
        if (loop) {
            openFile(loop);
            return;
        }
        getDirInfo(defaultDir);
    } else {
        generateVideoButtons(NULL);
        setContent();
    }
}

// Same as openFile, but for video folders.
void ThePlayer::openFolder(bool loop) {
    QFileDialog *dialog = new QFileDialog();
    dialog->setFileMode(QFileDialog::Directory);
    dialog->setNameFilter("Folder of video files");
    auto success = dialog->exec();
    int count = 0;
    if (success) {
        QStringList fnames = dialog->selectedFiles();
        count = getDirInfo(fnames.at(0).toStdString());
    }
    if (count == 0) {
        const int result = QMessageBox::information(
                    NULL,
                    QString("Tomeo"),
                    QString("no videos found! Try adding some videos to that folder."));
        if (loop) {
            openFolder(loop);
            return;
        }
        getDirInfo(defaultDir);
    } else {
        generateVideoButtons(NULL);
        setContent();
    }
}

// Toggles volume between 0 & 100.
void ThePlayer::audio() {
    if(volume() == 0){
        setVolume(100);
    }
    else {
        setVolume(0);
    }
}

// Returns true if no videos are available.
bool ThePlayer::empty() { return infos.size() == 0; }

// Connects various player controls.
void ThePlayer::connectAll() {
    // Connect video slider (seek bar)
    connect(videoSlider, SIGNAL(valueChanged(int)), this, SLOT(connectSlider(int)));
    connect(videoSlider, SIGNAL(sliderMoved(int)), this, SLOT(sliderPositionChanged(int)));
    connect(this, SIGNAL(positionChanged(qint64)), this, SLOT(positionChanged(qint64)));
    connect(this, SIGNAL(durationChanged(qint64)), this, SLOT(durationChanged(qint64)));

    // Connect position label
    connect(this, SIGNAL(positionChanged(qint64)), this, SLOT(positionText(qint64)));

    // Connect speed adjuster button
    connect(slowMoButton, SIGNAL(clicked()), this, SLOT(slowMo()));
    // Connect speed slider
    connect(speedSlider, SIGNAL(valueChanged(int)), this, SLOT(changeSpeed(int)));
    connect(window->audio, SIGNAL(clicked()), this, SLOT(audio()));
}
