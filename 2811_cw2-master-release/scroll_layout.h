#ifndef SCROLL_LAYOUT_H
#define SCROLL_LAYOUT_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include <QScrollArea>

// The layout for the left-side scrollArea which holds video thumbnail buttons.
class ScrollLayout: public QLayout{
public:
    ScrollLayout(): QLayout(){}
    ~ScrollLayout();

    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);
    int totalHeight;


private:
    QList<QLayoutItem*> list_;
};

#endif // SCROLL_LAYOUT_H
