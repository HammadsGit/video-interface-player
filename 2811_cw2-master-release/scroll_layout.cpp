#include "scroll_layout.h"
#include <iostream>
#include <QScrollArea>
#include "the_button.h"

void ScrollLayout::setGeometry(const QRect &r){
    QLayout::setGeometry(r);
    int count = 10;


    for (int i = 0; i < list_.size(); i++) {
        QLayoutItem *o = list_.at(i);

        // Default height for non-video widgets (currently not used since all widgets are videos)
        auto widgetHeight = 200;

        if (auto *button = dynamic_cast<TheButton*>(o->widget())) {
            auto thumbWidth = r.width()-10;
            // Calculate height based on aspect ratio of video thumbnail
            auto thumbHeight = double(thumbWidth)/button->info->aspectRatio;
            widgetHeight = thumbHeight+80;
            o->widget()->setGeometry(5, count, thumbWidth, thumbHeight+30);
            button->setIconSize(QSize(thumbWidth, thumbHeight));
        } else {
            o->widget()->setGeometry(5,count, r.width()-10, widgetHeight);
        }

        count = count + widgetHeight;
    }
    // Used by ResponsiveLayout to set the parent widget's height.
    totalHeight = count;
}

int ScrollLayout::count() const {
    return list_.size();
}

QLayoutItem *ScrollLayout::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *ScrollLayout::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void ScrollLayout::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize ScrollLayout::sizeHint() const {
    return minimumSize();
}

QSize ScrollLayout::minimumSize() const {
    return QSize(140,880);
}

ScrollLayout::~ScrollLayout() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}

