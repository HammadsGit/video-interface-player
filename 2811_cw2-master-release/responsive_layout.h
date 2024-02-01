#ifndef RESPONSIVELAYOUT_H
#define RESPONSIVELAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include <QScrollArea>
#include <QSlider>
#include <QtWidgets/QVBoxLayout>
#include "scroll_layout.h"

// The main layout of the window.
class ResponsiveLayout : public QLayout {
    Q_OBJECT
public:
    ResponsiveLayout(): QLayout() {}
    ~ResponsiveLayout();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    QScrollArea *files_scrollArea = new QScrollArea;
    QWidget *optionsRight = new QWidget;
    QWidget *player = new QWidget;
    QWidget *optionsButton = new QWidget;
    ScrollLayout *scrollLayout;
    bool show = false;
private:
    QList<QLayoutItem*> list_;

public slots:
    void showOptions();
    void doRedraw();
};
#endif // RESPONSIVELAYOUT_H

