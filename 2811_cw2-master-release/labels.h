#ifndef LABELS_H
#define LABELS_H

#include <QLabel>
#include <QString>
#include <QPushButton>
#include <map>
#include "darkmode.h"

/* Default strings for buttons, labels, etc.
 * Redefinitions of these in other languages can be found in languages.h. */
const QString
        kMedia = "Media",
        kDark = "Change Colour Theme",
        kAudio = "Audio On/Off",
        kEnglish = "English",
        kChinese = "Chinese",
        kTurkish = "Turkish",
        kTransitions = "Transitions",
        kSlowmo = "",
        kSize = "Size",
        kPosition = "Position",
        kRotation = "Rotation",
        kSpeed = "Speed",
        kExport = "Export,",
        kOpacity = "Opacity";


// Colors for light mode
const std::map<QString, QString> kColours = {
        std::make_pair(kMedia, "#fafafa"),
        std::make_pair(kAudio, "#fafafa"),
        std::make_pair(kDark, "#fafafa"),
        std::make_pair(kEnglish, "#fafafa"),
        std::make_pair(kChinese, "#fafafa"),
        std::make_pair(kTurkish, "#fafafa"),
        std::make_pair(kTransitions, "#fafafa"),
        std::make_pair(kSlowmo, "#fafafa"),
        std::make_pair(kSize, "#ffaaaa"),
        std::make_pair(kSpeed, "#fafafa"),
        std::make_pair(kPosition, "#aaffaa"),
        std::make_pair(kRotation, "#ffa9d3"),
        std::make_pair(kExport, "#ffa9d3"),
        std::make_pair(kOpacity, "#ffaa66"),
    };

// Colors for dark mode
const std::map<QString, QString> kDarkColours = {
        std::make_pair(kMedia, "#94908f"),
        std::make_pair(kAudio, "#94908f"),
        std::make_pair(kDark, "#94908f"),
        std::make_pair(kEnglish, "#94908f"),
        std::make_pair(kChinese, "#94908f"),
        std::make_pair(kTurkish, "#94908f"),
        std::make_pair(kTransitions, "#94908f"),
        std::make_pair(kSlowmo, "#94908f"),
        std::make_pair(kSize, "#ffaaaa"),
        std::make_pair(kSpeed, "#94908f"),
        std::make_pair(kPosition, "#aaffaa"),
        std::make_pair(kRotation, "#ffa9d3"),
        std::make_pair(kExport, "#ffa9d3"),
        std::make_pair(kOpacity, "#ffaa66"),
    };

// Potentially unnecessary forward definition
class window_widget;

class labels : public QPushButton {
    Q_OBJECT
public:
    labels(QString name, GlobalDarkMode *signaller) ;
    labels(QString name, QString colour, GlobalDarkMode *signaller) ;

    QString getName(){return name;}
private:
    QString name;
    void setStyle(QString colour);

public slots:
    // 1 = dark, 0 = light
    void darkMode(int x);
};


#endif // LABELS_H


