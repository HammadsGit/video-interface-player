#include "window_widget.h"
#include "languages.h"
#include <iostream>

void window_widget::dark_mode(){
    if (signaller->state() == false) {
        setStyleSheet("background-color: #2f3030;"
                      "color: white;");
        signaller->setDarkMode(1);
    } else {
        setStyleSheet("background-color: white;"
                      "color: black;");
        signaller->setDarkMode(0);
    }
}

// Get string in the current language. Indexes can be found in translation.h.
QString window_widget::getString(int index) {
    return currentLang[index];
}

// Apply a set language to buttons, and emit signal so other widgets can.
void window_widget::applyLang() {
    // Patch in missing strings from base lang
    if (currentLang.length() < baseLang.length()) {
        for (int i = currentLang.length(); i < baseLang.length(); i++)
            currentLang.append(baseLang[i]);
    }
    media->setText(getString(0));
    backgroundMode->setText(getString(1));
    audio->setText(getString(2));
    transition->setText(getString(4));
    emit languageChanged(currentLang);
}

void window_widget::change_english() {
    languages lang;
    currentLang = lang.English;
    applyLang();
    QLocale *locale = new QLocale("en_GB");
    emit localeChanged(locale);
}

void window_widget::change_chinese() {
    languages lang;
    currentLang = lang.Chinese;
    applyLang();
    QLocale *locale = new QLocale("zh_CN");
    emit localeChanged(locale);
}

void window_widget::change_turkish() {
    languages lang;
    currentLang = lang.Turkish;
    applyLang();
    QLocale *locale = new QLocale("tr_TR");
    emit localeChanged(locale);
}

// Connects various non-player related buttons to their actions.
void window_widget::connectAll() {
    connect(backgroundMode, SIGNAL(clicked()), this, SLOT(dark_mode()));
    connect(english, SIGNAL(clicked()), this, SLOT(change_english()));
    connect(chinese, SIGNAL(clicked()), this, SLOT(change_chinese()));
    connect(turkish, SIGNAL(clicked()), this, SLOT(change_turkish()));

    connect(media, SIGNAL(clicked()), top, SLOT(showOptions()));
}
