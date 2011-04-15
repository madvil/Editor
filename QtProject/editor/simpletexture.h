#ifndef SIMPLETEXTURE_H
#define SIMPLETEXTURE_H

#include <QObject>
#include <QPixmap>

class SimpleTexture : public QObject
{
    Q_OBJECT
public:
    SimpleTexture(QObject *parent = 0) : QObject(parent) { pixmap = 0; }

    QPixmap *pixmap;
    QString path;
};

#endif // SIMPLETEXTURE_H
