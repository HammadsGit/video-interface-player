#ifndef DARKMODE_H
#define DARKMODE_H

#include <QWidget>

/* This class' only use is to forward dark mode signals from the main window
 * in order to avoid circular dependencies. */
class GlobalDarkMode : public QWidget
{
    Q_OBJECT
public:
    GlobalDarkMode(): QWidget() {
        _state = 1;
    };
    void setDarkMode(int x) {
        _state = x;
        emit darkMode(x);
    };
    bool state() { return _state == 1 ? true : false; }
signals:
    void darkMode(int x);
private:
    int _state;
};

#endif // DARKMODE_H
