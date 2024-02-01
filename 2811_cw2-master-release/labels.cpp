#include <QFrame>
#include <QSize>
#include "labels.h"
#include <iostream>

labels::labels(QString name, GlobalDarkMode *signaller) : labels(name, kDarkColours.at(name), signaller) {}

labels::labels(QString name, QString colour, GlobalDarkMode *signaller) : QPushButton(), name(name) {
    setText(name);
    setStyle(colour);
    connect(signaller, SIGNAL(darkMode(int)), this, SLOT(darkMode(int)));
}

void labels::setStyle(QString colour) {
    QColor qc (colour);
     // Darker colour for the border
    qc = qc.darker(150);

    // make a nice looking label for the layout
    setStyleSheet("border: 1px solid "+ qc.name() +"; border-radius: 4px; background-color : "+
                  colour+"; color : black;");
}

void labels::darkMode(int x) {
    setStyle(x ? kDarkColours.at(name) : kColours.at(name));
}
