#ifndef TEXTURESMANAGER_H
#define TEXTURESMANAGER_H

#include <QObject>
#include <QPixmap>
#include <QListWidget>
#include <QDebug>

class TexturesManager : public QObject
{
    Q_OBJECT
public:
    TexturesManager(QListWidget *parent = 0);
    ~TexturesManager();

    static TexturesManager *getInstance();

    QPixmap *getNone();

protected:
    QListWidget *parent;

};

#endif // TEXTURESMANAGER_H
