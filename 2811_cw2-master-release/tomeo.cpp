//    ______
//   /_  __/___  ____ ___  ___  ____
//    / / / __ \/ __ `__ \/ _ \/ __ \
//   / / / /_/ / / / / / /  __/ /_/ /
//  /_/  \____/_/ /_/ /_/\___/\____/
//              video for sports enthusiasts...
//
//

#include <iostream>
#include <QApplication>
#include <QtMultimediaWidgets/QVideoWidget>
#include <QMediaPlaylist>
#include <string>
#include <vector>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QHBoxLayout>
#include <QtCore/QFileInfo>
#include <QtWidgets/QFileIconProvider>
#include <QDesktopServices>
#include <QImageReader>
#include <QMessageBox>
#include <QScrollArea>
#include <QtCore/QDir>
#include <QtCore/QDirIterator>
#include "the_player.h"
#include "the_button.h"
#include "QShortcut"
#include "scroll_layout.h"
#include "responsive_layout.h"
#include "darkmode.h"
#include "labels.h"
#include <QScrollArea>
#include <QSlider>
#include "main_window.h"
#include <QPushButton>
#include "shortcuts.h"
#include "menu_bar.h"
#include <icons.h>
#include "window_widget.h"
#include "options_right.h"
#include "icons.h"

#include "video_widget.h"


#include <QScrollArea>
#include "video_widget.h"
#include "darkmode.h"


#define GRID_BUTTON_SIZE 30


int main(int argc, char *argv[]) {

    // let's just check that Qt is operational first
    qDebug() << "Qt version: " << QT_VERSION_STR << Qt::endl;

    // Better looking icons
    QApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);
    // QApplication::setAttribute(Qt::AA_DontUseNativeMenuBar);

    // create the Qt Application
    QApplication app(argc, argv);

    // Create dark mode signaller for labels
    GlobalDarkMode *darkModeSignaller = new GlobalDarkMode();

    // The main window layout.
    ResponsiveLayout *top = new ResponsiveLayout();

    // The main window widget
    window_widget window(top, darkModeSignaller);
    window.setWindowTitle("Tomeo");
    window.setMinimumSize(600, 400);

    // Layout for video thumbnails on the left side.
    ScrollLayout *layout = new ScrollLayout();

    // the QMediaPlayer which controls the playback.
    ThePlayer *player = new ThePlayer(&window, layout);

    int videoCount = 0;
    if (argc == 2) {
        videoCount = player->getDirInfo(std::string(argv[1]), false);
        // Store as a default
        player->setDefaultDir(std::string(argv[1]));
    }

    if (videoCount == 0) {
        QMessageBox filePrompt;
        filePrompt.setIcon(QMessageBox::Information);
        filePrompt.setText("<strong>No files found.</strong>");
        filePrompt.setInformativeText("To start, choose to open a video or folder below, or quit and pass a video folder as a command-line argument.");
        QAbstractButton *buttonQuit = filePrompt.addButton("Quit", QMessageBox::DestructiveRole);
        QAbstractButton *buttonOpenFile = filePrompt.addButton("Open File", QMessageBox::ActionRole);
        QAbstractButton *buttonOpenFolder = filePrompt.addButton("Open Folder", QMessageBox::ActionRole);
        filePrompt.exec();
        auto clicked = filePrompt.clickedButton();
        if (clicked == buttonOpenFile) {
            player->openFile(true);
        } else if (clicked == buttonOpenFolder) {
            player->openFolder(true);
        } else {
            app.quit();
            exit(0);
        }
    }


    // Subclassed QVideoWidget that listens for mouse clicks for play/pause and ff/rw.
    ClickableVideoWidget *videoWidget = new ClickableVideoWidget();
    player->setVideoOutput(videoWidget);

    // Set up the scrollbar in the left scrollArea.
    top->files_scrollArea->horizontalScrollBarPolicy();
    top->files_scrollArea->setWidgetResizable(true);

    // Connection for triggering main window redraws, used when new videos are opened to reload the scrollArea.
    window.connect(player, SIGNAL(requestRedraw()), top, SLOT(doRedraw()));


    // This widget goes in the left side scrollArea and holds video thumbnails.
    QWidget *ScrollAreaContent = new QWidget();
    ScrollAreaContent->setLayout(layout);
    top->scrollLayout = layout;
    top->files_scrollArea->setWidget(ScrollAreaContent);

    // Generate video thumbnail buttons if not already done through the file picker.
    if (videoCount != 0) {
        player->generateVideoButtons(ScrollAreaContent, false);
    }

    // If there's videos, play the first one
    if (!player->empty())
        player->setContent();

    // Layout for the center panel which holds the player and primary controls
    QVBoxLayout *videoPlayer = new QVBoxLayout();

    videoPlayer->addWidget(videoWidget);

    // Video position label
    videoPlayer->addWidget(player->playerPosition);
    // Video position slider (seek bar)
    player->videoSlider->setMinimum(0);
    videoPlayer->addWidget(player->videoSlider);

    // Add the Play/Pause, FF, RW, and frame skip buttons to the button section
    QHBoxLayout *buttonRowLayout = new QHBoxLayout();
    player->playPauseButton->setMaximumWidth(GRID_BUTTON_SIZE);
    player->skipForwardButton->setMaximumWidth(GRID_BUTTON_SIZE);
    player->skipBackwardButton->setMaximumWidth(GRID_BUTTON_SIZE);
    player->skipFrameForwardButton->setMaximumWidth(GRID_BUTTON_SIZE);
    player->skipFrameBackwardButton->setMaximumWidth(GRID_BUTTON_SIZE);

    buttonRowLayout->addWidget(player->skipFrameBackwardButton);
    buttonRowLayout->addWidget(player->skipBackwardButton);
    buttonRowLayout->addWidget(player->playPauseButton);
    buttonRowLayout->addWidget(player->skipForwardButton);
    buttonRowLayout->addWidget(player->skipFrameForwardButton);

    // Add the button section to the center panel
    QWidget *buttonRow = new QWidget();
    buttonRow->setLayout(buttonRowLayout);
    videoPlayer->addWidget(buttonRow);
    // and add that to the main window.
    top->player->setLayout(videoPlayer);

    // Create the right side options panel.
    Options *optionsRight = new Options();

    // Create and add the speed adjuster to options
    player->slowMoButton = new labels(kSpeed, darkModeSignaller);
    player->slowMoButton->setText(kSpeed + " (100%)");
    optionsRight->addWidget(player->slowMoButton);
    player->speedSlider->setMinimum(25);
    player->speedSlider->setMaximum(200);
    player->speedSlider->setTickInterval(25);
    player->speedSlider->setTickPosition(QSlider::TicksAbove);
    player->speedSlider->setValue(100);
    optionsRight->addWidget(player->speedSlider);
    // Add the audio control,
    optionsRight->addWidget(window.audio);
    // the backgound mode control,
    optionsRight->addWidget(window.backgroundMode);

    // the language selectors,
    QHBoxLayout *language = new QHBoxLayout();
    language->addWidget(window.english);
    language->addWidget(window.chinese);
    language->addWidget(window.turkish);
    // hide extra padding on sides so the hbox aligns with other buttons
    language->setContentsMargins(0, 0, 0, 0);

    QWidget *language_layout = new QWidget();
    language_layout->setLayout(language);
    optionsRight->addWidget(language_layout);

    // and finally the transitions button.
    optionsRight->addWidget(window.transition);

    top->optionsRight->setLayout(optionsRight);

    top->optionsButton = window.media;


    // Add previously created components to main window
    top->addWidget(top->player);
    top->addWidget(top->files_scrollArea);
    top->addWidget(top->optionsRight);
    top->addWidget(top->optionsButton);
    // top->addWidget(window.backgroundMode);


    // Set up various global shortcuts & click actions (see shortcuts.h for bindings)
    // Play/Pause
    auto playPauseShortcut = new QShortcut(&window);
    playPauseShortcut->setKey(SHORTCUT_PLAYPAUSE);
    window.connect(playPauseShortcut, SIGNAL(activated()), player, SLOT(playPause()));
    window.connect(videoWidget, SIGNAL(videoClicked()), player, SLOT(playPause()));
    // Skip forward
    auto ffShortcut = new QShortcut(&window);
    ffShortcut->setKey(SHORTCUT_FF);
    window.connect(ffShortcut, SIGNAL(activated()), player, SLOT(skipForward()));
    window.connect(videoWidget, SIGNAL(rightHalfClicked()), player, SLOT(skipForward()));
    // Skip backward
    auto rwShortcut = new QShortcut(&window);
    rwShortcut->setKey(SHORTCUT_RW);
    window.connect(rwShortcut, SIGNAL(activated()), player, SLOT(skipBackward()));
    window.connect(videoWidget, SIGNAL(leftHalfClicked()), player, SLOT(skipBackward()));
    // Skip forward 1 frame
    auto ffFrameShortcut = new QShortcut(&window);
    ffFrameShortcut->setKey(SHORTCUT_FF_FRAME);
    window.connect(ffFrameShortcut, SIGNAL(activated()), player, SLOT(skipFrameForward()));
    // Skip backward 1 frame
    auto rwFrameShortcut = new QShortcut(&window);
    rwFrameShortcut->setKey(SHORTCUT_RW_FRAME);
    window.connect(rwFrameShortcut, SIGNAL(activated()), player, SLOT(skipFrameBackward()));

    // Finalize player control connections
    player->connectAll();

    window.setStyleSheet("background-color: #2f3030;"
                         "color: white;");
    // Finalize non-player control connections
    window.connectAll();

    // Create the main window object (confusing, but this contains the "window" variable).
    MainWindow *mainWindow = new MainWindow();
    mainWindow->setCentralWidget(&window);
    // Make sure the window is transparent and lets mouse events through
    mainWindow->setAttribute(Qt::WA_TransparentForMouseEvents, true);

    // Create the menu bar
    MenuBar *bar = new MenuBar(&window, player);

    // Make sure all text is set (in English by default)
    window.change_english();

    // Add menubar to mainWindow
    mainWindow->setMenuBar(bar);

    // Show the main window
    mainWindow->show();

    // wait for the app to terminate
    return app.exec();
}
