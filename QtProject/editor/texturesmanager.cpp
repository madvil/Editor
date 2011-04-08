#include "texturesmanager.h"

static TexturesManager *singletone = 0;
static QPixmap *none = 0;

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
