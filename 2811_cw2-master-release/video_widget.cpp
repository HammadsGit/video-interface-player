#include "video_widget.h"
#include "QMouseEvent"
#include <iostream>

// Percentage of the video's width on each side to register ff/rw clicks.
#define HALF_WIDTH_PCT 20

void ClickableVideoWidget::mousePressEvent(QMouseEvent *event) {
    qDebug() << "MousePress" << Qt::endl;
    if (event->button() == Qt::LeftButton) {
        emit videoClicked();
    }
}

void ClickableVideoWidget::mouseDoubleClickEvent(QMouseEvent *event) {
    if (event->button() == Qt::LeftButton) {
        auto pos = event->localPos();
        qDebug() << "Clicked @ (" << pos.x() << "," << pos.y() << ")" << Qt::endl;
        int leftCutoff = float(width()) * (float(HALF_WIDTH_PCT)/100.0f);
        int rightCutoff = width()-leftCutoff;
        if (pos.x() <= leftCutoff) emit leftHalfClicked();
        else if (pos.x() >= rightCutoff) emit rightHalfClicked();
    }
}


