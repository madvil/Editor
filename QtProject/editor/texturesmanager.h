#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H

#include <QObject>
#include <QVector>
#include <QListWidget>
#include <QDebug>
#include "simpletexture.h"

class GLWidget;

class TexturesManager : public QObject
{
    Q_OBJECT
public:
    TexturesManager(QListWidget *parent, GLWidget *glWidget);
    ~TexturesManager();

    static TexturesManager *getInstance();

    SimpleTexture *getNone();
    void addTexture(QString path);
    SimpleTexture *getTexture(QString path);
    QString getPath(unsigned id);

    int count();
    QString getPathByInd(int ind);

protected:
    QListWidget *parent;

};

#endif // TEXTURESMANAGER_H
