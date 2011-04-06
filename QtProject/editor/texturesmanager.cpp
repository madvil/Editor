#include "texturesmanager.h"

static TexturesManager *singletone = 0;

TexturesManager::TexturesManager(QListWidget *parent) : QObject(parent)
{
    singletone = this;
    this->parent = parent;
    qDebug() << 222;
    none = QPixmap(":/textures/media/none.png");
}

TexturesManager::~TexturesManager()
{
//    delete none;
}

TexturesManager *TexturesManager::getInstance()
{
    return singletone;
}
