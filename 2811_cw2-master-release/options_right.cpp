#include "options_right.h"
#include "labels.h"

#include <QString>
#include <string>
#include <sstream>
#include <iostream>
#include <iomanip>
#include <cmath>
#include <QFileDialog>
#include <stdio.h>

void Options::setGeometry(const QRect &r) {

    QLayout::setGeometry(r);
    int count = 0;
    for (int i = 0; i < list_.size(); i++) {
        QLayoutItem *o = list_.at(i);
        try {
            labels *label = static_cast<labels *>(o->widget());

            label->setGeometry(5,count * (r.height()/7 + 6) + 10, r.width()-10, r.height()/7);
            count = count + 1;
        }
        catch (std::bad_cast) {
            // bad_case: cast failed on reference...
            qDebug() << "Unknown widget in options panel" << Qt::endl;
        }
    }
}

int Options::count() const {
    return list_.size();
}

QLayoutItem *Options::itemAt(int idx) const {
    return list_.value(idx);
}

QLayoutItem *Options::takeAt(int idx) {
    return idx >= 0 && idx < list_.size() ? list_.takeAt(idx) : 0;
}

void Options::addItem(QLayoutItem *item) {
    list_.append(item);
}

QSize Options::sizeHint() const {
    return minimumSize();
}

QSize Options::minimumSize() const {
    return QSize(200, 400);

}

Options::~Options() {
    QLayoutItem *item;
    while ((item = takeAt(0)))
        delete item;
}
