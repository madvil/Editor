#include "texturesmanager.h"

static TexturesManager *singletone = 0;
static QPixmap *none = 0;
static QVector<SimpleTexture *> textures;

TexturesManager::TexturesManager(QListWidget *parent) : QObject(parent)
{
    singletone = this;
    this->parent = parent;
}

TexturesManager::~TexturesManager()
{
    //delete none;
}

TexturesManager *TexturesManager::getInstance()
{
    return singletone;
}

QPixmap *TexturesManager::getNone()
{
    if (none == 0)
        none = new QPixmap(":/textures/media/none.png");

    return none;
}

void TexturesManager::addTexture(QString path)
{
    SimpleTexture *st = new SimpleTexture;
    st->path = path;

    textures << st;
}

QPixmap *TexturesManager::getTexture(QString path)
{
    SimpleTexture *st = 0;
    foreach (SimpleTexture *st1, textures) {
        if (st1->path.compare(path) == 0) {
            st = st1;
            break;
        }
    }

    if (st != 0) {
        if (st->pixmap == 0) {
            st->pixmap = new QPixmap(st->path);
        }

        return st->pixmap;
    }

    return 0;
}

int TexturesManager::count()
{
    return textures.count();
}

QString TexturesManager::getPath(int ind)
{
    return textures.at(ind)->path;
}
