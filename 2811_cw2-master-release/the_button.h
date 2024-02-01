//
// Created by twak on 11/11/2019.
//

#ifndef CW2_THE_BUTTON_H
#define CW2_THE_BUTTON_H

#include <QToolButton>
#include <QUrl>
#include <QFileInfo>
#include <QLocale>
#include "window_widget.h"

// Holds information about a video (filename, icon, etc.) for use in a video thumbnail button.
class TheButtonInfo {

public:
    QUrl* url; // video file to play
    QIcon* icon; // icon to display
    QFileInfo file; // FileInfo for the file to display
    double aspectRatio; // Aspect ratio of file (w/h)
    TheButtonInfo ( QUrl* url, QIcon* icon, QFileInfo file, double aspectRatio) : url (url), icon (icon), file (file), aspectRatio(aspectRatio) {}
};

class TheButton : public QToolButton {
    Q_OBJECT

public:
    TheButtonInfo* info;

    TheButton(QWidget *parent, window_widget *window) :  QToolButton(parent) {
         connect(this, SIGNAL(released()), this, SLOT (clicked() )); // if QPushButton clicked...then run clicked() below
         // Receive locale changes for changing how file size is displayed.
         connect(window, SIGNAL(localeChanged(QLocale*)), this, SLOT(localeChanged(QLocale*)));
    }

    void init(TheButtonInfo* i);

private slots:
    void clicked();

public slots:
    void localeChanged(QLocale *locale);

signals:
    void jumpTo(TheButtonInfo*);

};

#endif //CW2_THE_BUTTON_H

