#ifndef MAIN_WINDOW_H
#define MAIN_WINDOW_H

#include <QtGui>
#include <QMainWindow>

// A basic (and currently unnecessary) subclass of QMainWindow.
class MainWindow: public QMainWindow {
    Q_OBJECT
public:
    MainWindow(): QMainWindow(){};
private:
};

#endif // MAIN_WINDOW_H
