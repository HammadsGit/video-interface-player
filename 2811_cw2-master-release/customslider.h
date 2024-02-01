#ifndef CUSTOMSLIDER_H
#define CUSTOMSLIDER_H

#include <QSlider>

class TheSlider : public QSlider {
    Q_OBJECT
public:
    TheSlider(): QSlider() {}
    ~TheSlider();
};

#endif // CUSTOMSLIDER_H
