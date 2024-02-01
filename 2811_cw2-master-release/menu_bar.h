#ifndef MENU_BAR_H
#define MENU_BAR_H

#include <QMenuBar>
#include <QAction>
#include <QMenu>
#include <QShortcut>
#include "shortcuts.h"
#include "the_player.h"

/* MenuBar is a subclass of QMenuBar that also
 * handles creating it's contents and making them functional. */
class MenuBar : public QMenuBar
{
    Q_OBJECT
public:
    MenuBar(window_widget *window, ThePlayer *player): QMenuBar() {
        fileMenu = addMenu("&File");

        openFile = new QAction("Open File", this);
        openFile->setShortcut(SHORTCUT_OPENFILE);
        openFile->setShortcutVisibleInContextMenu(true);
        openFile->setShortcutContext(Qt::ApplicationShortcut);
        fileMenu->addAction(openFile);
        connect(openFile, SIGNAL(triggered()), player, SLOT(openFile()));

        openFolder = new QAction("Open Folder", this);
        openFolder->setShortcut(SHORTCUT_OPENFOLDER);
        openFolder->setShortcutVisibleInContextMenu(true);
        openFile->setShortcutContext(Qt::ApplicationShortcut);
        fileMenu->addAction(openFolder);
        connect(openFolder, SIGNAL(triggered()), player, SLOT(openFolder()));


        settingsMenu = addMenu("&Settings");

        lightDarkToggle = new QAction("Change Colour Theme", this);
        lightDarkToggle->setShortcut(SHORTCUT_LIGHTDARK);
        lightDarkToggle->setShortcutVisibleInContextMenu(true);
        lightDarkToggle->setShortcutContext(Qt::ApplicationShortcut);
        settingsMenu->addAction(lightDarkToggle);
        connect(lightDarkToggle, SIGNAL(triggered()), window, SLOT(dark_mode()));


        languageMenu = addMenu("&Language");

        langEnglish = new QAction("English", this);
        languageMenu->addAction(langEnglish);
        connect(langEnglish, SIGNAL(triggered()), window, SLOT(change_english()));
        langChinese = new QAction("Chinese", this);
        languageMenu->addAction(langChinese);
        connect(langChinese, SIGNAL(triggered()), window, SLOT(change_chinese()));
        langTurkish = new QAction("Turkish", this);
        languageMenu->addAction(langTurkish);
        connect(langTurkish, SIGNAL(triggered()), window, SLOT(change_turkish()));

        connect(window, SIGNAL(languageChanged(QStringList)), this, SLOT(applyLanguage(QStringList)));
    };
    QMenu *fileMenu;
    QAction *openFile;
    QShortcut *openFileShortcut;
    QAction *openFolder;
    QShortcut *openFolderShortcut;

    QMenu *settingsMenu;
    QAction *lightDarkToggle;

    QMenu *languageMenu;
    QAction *langEnglish;
    QAction *langChinese;
    QAction *langTurkish;

public slots:
    void applyLanguage(QStringList lang) {
        fileMenu->setTitle(lang[15]);
        openFile->setText(lang[16]);
        openFolder->setText(lang[17]);

        settingsMenu->setTitle(lang[18]);
        lightDarkToggle->setText(lang[1]);

        languageMenu->setTitle(lang[19]);
    }
};

#endif // MENU_BAR_H
