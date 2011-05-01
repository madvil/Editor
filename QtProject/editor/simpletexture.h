#ifndef SIMPLETEXTURE_H
#define SIMPLETEXTURE_H

#include <QObject>

class SimpleTexture : public QObject
{
    Q_OBJECT
public:
    SimpleTexture(QObject *parent = 0) : QObject(parent) { id = 0; width = height = 1; }

    unsigned id;
    QString path;
    int width;
    int height;
};

#endif // SIMPLETEXTURE_H
