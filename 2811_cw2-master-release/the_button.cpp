//
// Created by twak on 11/11/2019.
//

#include "the_button.h"
#include <QFile>


void TheButton::init(TheButtonInfo* i) {
    setToolButtonStyle(Qt::ToolButtonTextUnderIcon);
    setIcon( *(i->icon) );

    info =  i;
    // Set default locale, which also causes the file size to display.
    localeChanged(new QLocale(("en_GB")));
}

void TheButton::localeChanged(QLocale *locale) {
    QFile *f = new QFile(info->file.filePath());
    f->open(QFile::ReadOnly);
    setText(info->file.fileName() + " (" + locale->formattedDataSize(f->size()) + ")");
    f->close();
}

void TheButton::clicked() {
    emit jumpTo(info);
}
