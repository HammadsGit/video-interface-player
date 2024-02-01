#ifndef ICONS_H
#define ICONS_H

#include <QByteArray>

// Raw SVG icon data, created in inkscape, compressed with svgo and then stored as variables for use in QIcons.
// Easier than reading from a file and risking the path messing up, and portable.
extern QByteArray playIconRaw;
extern QByteArray pauseIconRaw;
extern QByteArray ffIconRaw;
extern QByteArray rwIconRaw;
extern QByteArray missingThumbRaw;
extern QByteArray ffFrameIconRaw;
extern QByteArray rwFrameIconRaw;

#endif // ICONS_H
