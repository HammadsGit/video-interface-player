//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_PLAYER_H
#define CW2_THE_PLAYER_H


#include <QApplication>
#include <QMediaPlayer>
#include "the_button.h"
#include <vector>
#include <QTimer>
#include <QSlider>
#include <QLabel>
#include <QPushButton>
#include <QIcon>
#include <QPixmap>
#include "icons.h"
#include "shortcuts.h"
#include "labels.h"
#include "responsive_layout.h"
#include "window_widget.h"
#include "scroll_layout.h"

// Holds the video player, many of its controls, and the video thumbnail buttons.
class ThePlayer : public QMediaPlayer {

Q_OBJECT

private:
    std::vector<TheButtonInfo> infos;
    std::vector<TheButton*> buttons;
    long updateCount = 0;

    QString videoLength;
    QString durationToString(qint64 x) const;
    QIcon pauseIcon = QIcon(QPixmap::fromImage(QImage::fromData(pauseIconRaw)));
    QIcon playIcon = QIcon(QPixmap::fromImage(QImage::fromData(playIconRaw)));
    QIcon ffIcon = QIcon(QPixmap::fromImage(QImage::fromData(ffIconRaw)));
    QIcon rwIcon = QIcon(QPixmap::fromImage(QImage::fromData(rwIconRaw)));
    QIcon ffFrameIcon = QIcon(QPixmap::fromImage(QImage::fromData(ffFrameIconRaw)));
    QIcon rwFrameIcon = QIcon(QPixmap::fromImage(QImage::fromData(rwFrameIconRaw)));

    QString speedString = kSpeed;
    std::string defaultDir;

public:
    ThePlayer(window_widget *window, ScrollLayout *scrollLayout) : window(window), layout(scrollLayout), QMediaPlayer(NULL) {
        setVolume(0); // be slightly less annoying
        connect (this, SIGNAL (stateChanged(QMediaPlayer::State)), this, SLOT (playStateChanged(QMediaPlayer::State)) );
        connect(playPauseButton, SIGNAL(clicked()), this, SLOT(playPause()));
        connect(skipForwardButton, SIGNAL(clicked()), this, SLOT(skipForward()));
        connect(skipBackwardButton, SIGNAL(clicked()), this, SLOT(skipBackward()));
        connect(skipFrameForwardButton, SIGNAL(clicked()), this, SLOT(skipFrameForward()));
        connect(skipFrameBackwardButton, SIGNAL(clicked()), this, SLOT(skipFrameBackward()));

        connect(window, SIGNAL(languageChanged(QStringList)), this, SLOT(languageChanged(QStringList)));
    }

    labels *slowMoButton;

    QSlider *videoSlider = new QSlider(Qt::Horizontal);
    QSlider *speedSlider = new QSlider(Qt::Horizontal);

    QPushButton *playPauseButton = new QPushButton(pauseIcon, "");
    QPushButton *skipForwardButton = new QPushButton(ffIcon, "");
    QPushButton *skipBackwardButton = new QPushButton(rwIcon, "");
    QPushButton *skipFrameForwardButton = new QPushButton(ffFrameIcon, "");
    QPushButton *skipFrameBackwardButton = new QPushButton(rwFrameIcon, "");

    QLabel *playerPosition = new QLabel();

    QImage missingThumbImage = QImage::fromData(missingThumbRaw);
    QIcon *missingThumb = new QIcon(QPixmap::fromImage(missingThumbImage));

    ScrollLayout *layout;
    QWidget *buttonWidget = NULL;
    window_widget *window;

    void setDefaultDir(std::string loc);
    // returns number of videos
    int getDirInfo(std::string loc, bool clear = true, bool isFile = false);
    void generateVideoButtons(QWidget *videoButtonsWidget, bool clear = true);
    // Starts playing the first video once things have been set up by the above two
    void setContent();
    bool empty();
    void connectAll();

private:
    int passedPlaybackRate = 100;
    void addVideoFile(QString f);

signals:
    void requestRedraw();

private slots:
    void playStateChanged (QMediaPlayer::State ms);

public slots:
    // start playing this ButtonInfo
    void jumpTo (TheButtonInfo* button);
    void playPause();

    void skipForward();
    void skipBackward();
    void skipFrameForward();
    void skipFrameBackward();
    void connectSlider(int x);
    // Same as above, but runs when the user is actively moving the slider.
    void sliderPositionChanged(int x);
    void positionChanged(qint64 x);
    void durationChanged(qint64 x);
    void slowMo();
    void changeSpeed(int x);

    void positionText(qint64 x);
    void openFile(bool loop = false);
    void openFolder(bool loop = false);

    void audio();

    void languageChanged(QStringList lang);
};

#endif //CW2_THE_PLAYER_H
