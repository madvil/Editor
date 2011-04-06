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

    QPixmap getNone() { qDebug() << 12331; return none; }

protected:
    QListWidget *parent;
    QPixmap none;
};

#endif // TEXTURESMANAGER_H
