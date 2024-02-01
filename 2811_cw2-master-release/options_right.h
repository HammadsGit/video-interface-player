#ifndef OPTIONS_RIGHT_H
#define OPTIONS_RIGHT_H

#include <QtGui>
#include <QList>
#include <QLayout>
#include <QScrollArea>
#include <QSlider>
#include <QtWidgets/QVBoxLayout>

// Options holds the content of the right-side panel.
class Options : public QLayout {
public:
    Options(): QLayout() {}
    ~Options();

    // standard functions for a QLayout
    void setGeometry(const QRect &rect);

    void addItem(QLayoutItem *item);
    QSize sizeHint() const;
    QSize minimumSize() const;
    int count() const;
    QLayoutItem *itemAt(int) const;
    QLayoutItem *takeAt(int);

private:
    QList<QLayoutItem*> list_;
};

#endif // OPTIONS_RIGHT_H
