#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H

#include <QObject>
#include <QVector>
#include <QPixmap>
#include <QListWidget>
#include <QDebug>
#include "simpletexture.h"

class TexturesManager : public QObject
{
    Q_OBJECT
public:
    TexturesManager(QListWidget *parent = 0);
    ~TexturesManager();

    static TexturesManager *getInstance();

    QPixmap *getNone();
    void addTexture(QString path);
    QPixmap *getTexture(QString path);
    QString getPath(QPixmap *pixmap);

    int count();
    QString getPath(int ind);

protected:
    QListWidget *parent;

};

#endif // TEXTURESMANAGER_H
