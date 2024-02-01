//
// Created by twak on 11/11/2019.
//

#ifndef CW2_VIDEO_WIDGET_H
#define CW2_VIDEO_WIDGET_H


#include <QApplication>
#include <QVideoWidget>
#include "the_button.h"
#include <vector>
#include <QTimer>

//  Subclassed QVideoWidget that handles mouse clicks.
class ClickableVideoWidget : public QVideoWidget {

Q_OBJECT


public slots:
    void mousePressEvent(QMouseEvent *event) override;
    void mouseDoubleClickEvent(QMouseEvent *event) override;

signals:
    void videoClicked();
    void leftHalfClicked();
    void rightHalfClicked();
    int getDuration();
};

#endif //CW2_VIDEO_WIDGET_H
