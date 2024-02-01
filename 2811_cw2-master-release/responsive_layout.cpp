#include "responsive_layout.h"
#include "labels.h"
#include <iostream>
#include "window_widget.h"

// Width below which the options panel should be hidden
#define BP_HIDE_OPTIONS 800

void ResponsiveLayout::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);
    const int optionsWidth = 220;
    // For small windows, hide the options panel.
    if (r.width() < BP_HIDE_OPTIONS) {
        if (show) {
            optionsButton->setGeometry(r.width()/5 + 5, 0, r.width() - (optionsWidth+10) -r.width()/5, 30);
            optionsRight->setGeometry(r.width() - optionsWidth, 0+r.y(), optionsWidth, r.height());
        } else {
            optionsButton->setGeometry(r.width()/5 + 5, 0, r.width() - r.width()/5 - 10, 30);
            // Hide the panel
            optionsRight->setGeometry(-1, -1, 0, 0);
        }
        // Draw the central player
        player->setGeometry(r.width()/5, 30+r.y(), r.width() - (r.width()/5), r.height()-30);
        // Draw the files on the left side
        files_scrollArea->setGeometry(0, 0+r.y(), r.width()/5, r.height());

    } else {
        // Ensure the options panel is hidden at first if the window is made small
        show = false;
        // Hide the options toggle since it always appears
        optionsButton->setGeometry(-1, -1, 0, 0);
        // Draw the options panel
        optionsRight->setGeometry(r.width() - optionsWidth, 0+r.y(), optionsWidth, r.height());
        // Draw the files on the left side
        files_scrollArea->setGeometry(r);
        files_scrollArea->setGeometry(0, 0+r.y(), r.width()/5, r.height());
        // Make sure the scrollArea's content has the right height for its content
        files_scrollArea->widget()->setFixedHeight(scrollLayout->totalHeight);
        // Draw the central player
        player->setGeometry(r.width()/5, 0+r.y(), r.width() - optionsWidth - r.width()/5, r.height());
    }
}

int ResponsiveLayout::count() const {
    return list_.size();
}

QLayoutItem *ResponsiveLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ResponsiveLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ResponsiveLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ResponsiveLayout::sizeHint() const {
    return minimumSize();
}

QSize ResponsiveLayout::minimumSize() const {
    return QSize(800, 680);

}

ResponsiveLayout::~ResponsiveLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

void ResponsiveLayout::showOptions() {
    show = !show;
    doRedraw();
}

void ResponsiveLayout::doRedraw() {
    qDebug() << "Redraw requested" << Qt::endl;
    update();
}

