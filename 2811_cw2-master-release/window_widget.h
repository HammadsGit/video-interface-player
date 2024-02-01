#ifndef WINDOW_WIDGET_H
#define WINDOW_WIDGET_H
#include "labels.h"
#include "languages.h"
#include "darkmode.h"
#include "responsive_layout.h"

#include <QWidget>
#include <QLocale>

// The main window widget, also handles things like language changes and some button functionality.
class window_widget : public QWidget
{
    Q_OBJECT
public:
    window_widget(ResponsiveLayout *top, GlobalDarkMode *darkModeSignaller): top(top), QWidget() {
        signaller = darkModeSignaller;
        languages lang;
        currentLang = lang.English;
        baseLang = lang.English;
        media = new labels(kMedia, signaller);
        audio = new labels(kAudio, signaller);
        backgroundMode = new labels(kDark, signaller);
        english = new labels(kEnglish, signaller);
        english->setFixedHeight(30);
        chinese = new labels(kChinese, signaller);
        chinese->setFixedHeight(30);
        turkish = new labels(kTurkish, signaller);
        turkish->setFixedHeight(30);
        transition = new labels(kTransitions, signaller);

        setLayout(top);
    };

    GlobalDarkMode *signaller;
    labels *media;
    labels *audio;
    labels *backgroundMode;
    labels *english;
    labels *chinese;
    labels *turkish;
    labels *transition;
    QStringList baseLang;
    QStringList currentLang;
    ResponsiveLayout *top;

    QString getString(int index);

    void connectAll();

signals:
    void languageChanged(QStringList lang);
    void localeChanged(QLocale *locale);

private:
    void applyLang();


public slots:
    void dark_mode();
    void change_english();
    void change_chinese();
    void change_turkish();

};

#endif // WINDOW_WIDGET_H
