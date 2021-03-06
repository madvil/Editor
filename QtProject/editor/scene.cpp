#include <qtimer.h>
#include <QDebug>
#include "scene.h"
#include "mainwindow.h"
#include "constants.h"

Scene::Scene(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(SCENE_NAME);
    init();

    drawDebugInfo = true;
    sliding = 0;
    animSliding = 0;
    translatingMovable = 0;
    lastHeight = 0;

    background = new Background(propertyBrowser);
    firstplan = new Firstplan(propertyBrowser);
    landscape = new Landscape(propertyBrowser);
    transformer = new Transformer(this);
    transparentBlack = QBrush(QColor(0, 0, 0, 90));
    transparentBlack.setStyle(Qt::Dense5Pattern);
    debugPen = QPen(Qt::white);
    debugPen.setWidth(1);

    name->setEnabled(false);
    targetDeviceGroup = addNewProperty("Target device", PropertyManagers::getInstance()->getGroupPropertyManager());
    tdHeight = addNewProperty("Height", PropertyManagers::getInstance()->getIntPropertyManager(), targetDeviceGroup);
    tdWidth = addNewProperty("Width", PropertyManagers::getInstance()->getIntPropertyManager(), targetDeviceGroup);
    worldHeight = addNewProperty("World height", PropertyManagers::getInstance()->getIntPropertyManager());

    setTDHeight(320);
    setTDWidth(480);
    setWorldHeight(1000);
}

void Scene::paint(QPainter *painter, QPaintEvent *event, GLWidget *glWidget)
{
    lastHeight = event->rect().height();
    int deltaHeight = (lastHeight / 6);

    painter->fillRect(event->rect(), *background->getBgColor());
    background->paint(painter, event, this);
    painter->translate(-sliding, 0);

    landscape->paint(painter, event, this);

    Movable *selectedMovable = 0;
    transformer->assignTo(0);
    foreach (Entity *obj, paintObjects) {
        obj->paint(painter, event, this);
        if (obj->isSelected())
            selectedMovable = obj;
    }

    landscape->paintFractures(painter, event, this);
    firstplan->paint(painter, event);

    //debug draws
    painter->resetMatrix();
    painter->setPen(debugPen);

    painter->fillRect(QRect(0, 0, event->rect().width(), deltaHeight), transparentBlack);
    painter->fillRect(QRect(0, deltaHeight * 5, event->rect().width(), deltaHeight * 6), transparentBlack);

    painter->setOpacity(0.6);

    painter->drawLine(QPoint(0, deltaHeight), QPoint(event->rect().width(), deltaHeight));
    painter->drawLine(QPoint(0, deltaHeight * 5), QPoint(event->rect().width(), deltaHeight * 5));

    painter->setOpacity(1.0);
    painter->translate(-sliding, 0);

    transformer->assignTo(selectedMovable);
    transformer->paint(painter, event);

    float r = getRatio();
    int h = getWorldHeight();
    int d = 100;
    if (h > 799) {
        d = 1000;
    } else if (h > 7999) {
        d = 10000;
    }

    int start = (sliding / r) / (float)d;
    int count = start + (event->rect().width() / r) / (float)d + 2;
    for (int i = start; i < count; i++) {
        painter->drawText((i * d) * r + 4, deltaHeight * 5 + 15, QString::number(i));
        painter->drawText((i * d) * r + 4, deltaHeight - 6, QString::number(i));
        painter->drawLine(QPoint((i * d) * r, deltaHeight), QPoint((i * d) * r, deltaHeight - 5));
        painter->drawLine(QPoint((i * d) * r, deltaHeight * 5), QPoint((i * d) * r, deltaHeight * 5 + 5));
    }

    float d_ = d;
    d = (float)getWorldHeight() * ((float)getTDWidth() / (float)getTDHeight());
    start = (sliding / r) / (float)d;
    count = start + (event->rect().width() / r) / (float)d + 2;
    for (int i = start; i < count; i++) {
        painter->drawLine(QPoint((i * d) * r, 0), QPoint((i * d) * r, event->rect().bottom()));
    }

    painter->resetMatrix();
    painter->drawText(5, deltaHeight - 20, "x" + QString::number(d_));
}

bool Scene::animate()
{
    if (animSliding != 0) {
        animSliding = (int)((float)animSliding * (0.95));
        slide(animSliding);

        if ((animSliding > 0 && animSliding < 0.001) || (animSliding < 0 && animSliding > -0.001))
            animSliding = 0;
    } else {
        return true;
    }

    return false;
}

void Scene::setTDHeight(int tdHeight)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->tdHeight, tdHeight);
}

void Scene::setTDWidth(int tdWidth)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->tdWidth, tdWidth);
}

void Scene::setWorldHeight(int worldHeight)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->worldHeight, worldHeight);
}

void Scene::save(QXmlStreamWriter *xml, bool toExport)
{
    xml->writeStartElement("scene");
    {
        if (!toExport) {
            xml->writeAttribute("target_height", tdHeight->valueText());
            xml->writeAttribute("target_width", tdWidth->valueText());
        }
        xml->writeAttribute("world_height", worldHeight->valueText());

        background->save(xml, toExport);
        firstplan->save(xml, toExport);
        landscape->save(xml, toExport);

        foreach (Entity *obj, paintObjects) {
            obj->save(xml, toExport);
        }
    }
    xml->writeEndElement();
}

void Scene::load(QXmlStreamReader *xml)
{
    xml->readNext();
    while (!xml->atEnd()) {
        if (xml->isEndElement()) {
            xml->readNext();
            break;
        }

        if (xml->isStartElement()) {
            if (xml->name() == "scene") {
                loadEntry(xml);
            }
        } else {
            xml->readNext();
        }
    }
}

void Scene::loadEntry(QXmlStreamReader *xml)
{
    paintObjects.clear();
    setTDHeight(xml->attributes().value("target_height").toString().toInt());
    setTDWidth(xml->attributes().value("target_width").toString().toInt());
    setWorldHeight(xml->attributes().value("world_height").toString().toInt());

    xml->readNext();
    while (!xml->atEnd()) {
        if (xml->isEndElement()) {
            xml->readNext();
            break;
        }

        if (xml->isStartElement()) {
            if (xml->name() == "background") {
                background->load(xml);
            } else if (xml->name() == "firstplan") {
                firstplan->load(xml);
            } else if (xml->name() == "landscape") {
                landscape->load(xml);
            } else if (xml->name() == "entity") {
                addEntity(0, 0, 0, 0)->load(xml);
            }
        } else {
            xml->readNext();
        }
    }
}

int Scene::convertWindowCoordToWorld(int w_y)
{
    int deltaHeight = (lastHeight / 6);
    float y = w_y - deltaHeight;
    y /= getRatio();

    return (int)y;
}

int Scene::convertWorldCoordToWindow(int y)
{
    int deltaHeight = (lastHeight / 6);
    float _y = y * getRatio();
    _y += deltaHeight;

    return _y;
}

float Scene::getRatio()
{
    int deltaHeight = (lastHeight / 6);
    return ((float)deltaHeight * 4.0) / (float)getWorldHeight();
}

Entity *Scene::addEntity(Entity *entity)
{
    paintObjects << entity;
    return entity;
}

Entity *Scene::addEntity(SimpleTexture *st)
{
    if (st == 0) {
        return 0;
    }

    float d = (float)getWorldHeight() / (float)getTDHeight();
    int w = st->width * d;
    int h = st->height * d;
    Entity *e = addEntity((sliding + 10) / getRatio(), getWorldHeight() / 2 - h / 2, w, w);
    e->setTex(st);

    return e;
}

Entity *Scene::addEntity(int x, int y, int width, int height)
{
    Entity *e = new Entity(propertyBrowser);
    e->setPosX(x);
    e->setPosY(y);
    e->setWidth(width);
    e->setHeight(height);

    return addEntity(e);
}

Entity *Scene::getEntity(int w_x, int w_y)
{
    Entity *e = 0;
    float r = getRatio();
    int x = (float)(w_x + sliding) / r;
    int y = convertWindowCoordToWorld(w_y);

    for (int i = paintObjects.count() - 1; i > -1; i--) {
        Entity *obj = paintObjects.at(i);
        obj->setCheckedCorner(false);
        int _x = obj->getPosX();
        int _y = obj->getPosY();

        if (x >= _x && x < _x + obj->getWidth()) {
            if (y >= _y && y < _y + obj->getHeight()) {
                e = obj;
                e->checkCorner(w_x, w_y, this);
                break;
            }
        }
    }

    return e;
}

Movable *Scene::getMovable(int w_x, int w_y)
{
    Movable *m = landscape->getMover(w_x, w_y);
    if (m != 0)
        return m;

    return getEntity(w_x, w_y);
}

void Scene::startModifyMovable(Movable *m)
{
    translatingMovable = m;
    translateX = 0;
    translateY = 0;
    if (m != 0) {
        startPosX = m->getPosX();
        startPosY = m->getPosY();
        startWidth = m->getWidth();
        startHeight = m->getHeight();
    }
}

void Scene::translateMovable(int dX, int dY)
{
    if (translatingMovable != 0) {
        translateX += dX;
        translateY += dY;
        translatingMovable->setPosX(startPosX - (float)translateX / getRatio());
        translatingMovable->setPosY(startPosY - (float)translateY / getRatio());
    }
}

void Scene::transformMovable(int dX, int dY)
{
    if (translatingMovable != 0) {
        translateX += dX;
        translateY += dY;
        translatingMovable->setWidth(startWidth - (float)translateX / getRatio());
        translatingMovable->setHeight(startHeight - (float)translateY / getRatio());
    }
}

void Scene::endModifyMovable()
{
    translateX = translateY = startPosX = startPosY = startWidth = startHeight = 0;
    if (translatingMovable!= 0) {
        translatingMovable->setCheckedCorner(false);
        translatingMovable = 0;
    }
}
