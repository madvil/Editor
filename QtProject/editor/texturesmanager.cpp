#include "texturesmanager.h"
#include "glwidget.h"

static TexturesManager *singletone = 0;
static GLWidget *_glWidget = 0;
static SimpleTexture *none = 0;
static QVector<SimpleTexture *> textures;

TexturesManager::TexturesManager(QListWidget *parent,  GLWidget *glWidget) : QObject(parent)
{
    singletone = this;
    this->parent = parent;
    _glWidget = glWidget;
}

TexturesManager::~TexturesManager()
{
    //delete none;
}

TexturesManager *TexturesManager::getInstance()
{
    return singletone;
}

SimpleTexture *TexturesManager::getNone()
{
    if (none == 0) {
        none = _glWidget->loadTexture(":/textures/media/none.png");
    }

    return none;
}

void TexturesManager::addTexture(QString path)
{
    SimpleTexture *st = new SimpleTexture;
    st->path = path;

    textures << st;
}

SimpleTexture *TexturesManager::getTexture(QString path)
{
    SimpleTexture *st = 0;
    foreach (SimpleTexture *st1, textures) {
        if (st1->path.compare(path) == 0) {
            st = st1;
            break;
        }
    }

    if (st != 0) {
        if (st->id == 0) {
            QFile file(path);
            if (file.exists()) {
                SimpleTexture *st1 = _glWidget->loadTexture(path);
                st->id = st1->id;
                st->width = st1->width;
                st->height = st1->height;
            }
        }

        return st;
    }

    return getNone();
}

QString TexturesManager::getPath(unsigned id)
{
    if (id != 0) {
        foreach (SimpleTexture *st, textures) {
            if (st->id == id) {
                return st->path;
            }
        }
    }

    return "none";
}

int TexturesManager::count()
{
    return textures.count();
}

QString TexturesManager::getPathByInd(int ind)
{
    return textures.at(ind)->path;
}
