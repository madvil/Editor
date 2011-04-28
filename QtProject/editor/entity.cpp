#include "entity.h"
#include "constants.h"
#include "propertymanagers.h"
#include "scene.h"
#include "texturesmanager.h"

static int ENTITY_COUNTER = 1;

Entity::Entity(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    setRootName(ENTITY_GROUP);
    setName(tr("Entity ") + QString::number(ENTITY_COUNTER++));
    init();
    checkedCorner = false;
    drawRect = false;
    pixmap = 0;

    geometryGroup = addNewProperty("Geometry", PropertyManagers::getInstance()->getGroupPropertyManager());
    posX = addNewProperty("X", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    posY = addNewProperty("Y", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    posZ = addNewProperty("Z", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    tX = addNewProperty("Texture X", PropertyManagers::getInstance()->getDoublePropertyManager(), geometryGroup);
    tY = addNewProperty("Texture Y", PropertyManagers::getInstance()->getDoublePropertyManager(), geometryGroup);
    angle = addNewProperty("Angle", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    width = addNewProperty("Width", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    height = addNewProperty("Height", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);

    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(angle, 0, 360);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(tX, 1.0);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(tY, 1.0);

    setTexX(1.0);
    setTexY(1.0);
}

void Entity::paint(QPainter *painter, QPaintEvent *event, Scene *scene)
{
    float ratio = scene->getRatio();
    int x = getPosX() * ratio;
    int y = scene->convertWorldCoordToWindow(getPosY());
    int w = getWidth() * ratio;
    int h = getHeight() * ratio;
    if (pixmap == 0)
        pixmap = TexturesManager::getInstance()->getNone();

    if (!((x - scene->getSlide() < 0 || x - scene->getSlide() > event->rect().width()) &&
                       (x + w - scene->getSlide() < 0 || x + w - scene->getSlide() > event->rect().width()))) {
        int _x = (int)getTexX();
        int _y = (int)getTexY();
        int _w = w / _x;
        int _h = h / _y;

        for (int i = 0; i < _x; i++) {
            for (int j = 0; j < _y; j++) {
                painter->drawPixmap(x + _w * i, y + _h * j, _w, _h, *pixmap);
            }
        }
//        painter->drawPixmap(x, y, w, h, *pixmap);
        if (!selected && drawRect)
            painter->drawRect(x, y, w, h);
    }
}

void Entity::translate(int dX, int dY)
{
    setPosX(getPosX() - dX);
    setPosY(getPosY() - dY);
}

void Entity::setPosX(int posX)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->posX, posX);
}

void Entity::setPosY(int posY)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->posY, posY);
}

void Entity::setPosZ(int posZ)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->posZ, posZ);
}

void Entity::setTexX(float tX)
{
    PropertyManagers::getInstance()->getDoublePropertyManager()->setValue(this->tX, tX);
}

void Entity::setTexY(float tY)
{
    PropertyManagers::getInstance()->getDoublePropertyManager()->setValue(this->tY, tY);
}

void Entity::setAngle(int angle)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->angle, angle);
}

void Entity::setWidth(int width)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->width, width);
}

void Entity::setHeight(int height)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->height, height);
}

bool Entity::checkCorner(int w_x, int w_y, Scene *scene)
{
    checkedCorner = false;
    int x_ = (getPosX() + getWidth()) * scene->getRatio() - scene->getSlide();
    int y_ = scene->convertWorldCoordToWindow(getPosY() + getHeight());
    if (w_x >= x_ - 10 && w_x <= x_) {
        if (w_y >= y_ - 10 && w_y <= y_)
            checkedCorner = true;
    }

    return checkedCorner;
}

void Entity::save(QXmlStreamWriter *xml, bool toExport)
{
    xml->writeStartElement("entity");
    {
        xml->writeAttribute("x", posX->valueText());
        xml->writeAttribute("y", posY->valueText());
        xml->writeAttribute("z", posZ->valueText());
        xml->writeAttribute("tx", tX->valueText());
        xml->writeAttribute("ty", tY->valueText());
        xml->writeAttribute("angle", angle->valueText());
        xml->writeAttribute("width", width->valueText());
        xml->writeAttribute("height", height->valueText());

        QFileInfo fInfo(TexturesManager::getInstance()->getPath(pixmap));
        if (toExport) {
            xml->writeAttribute("texture", fInfo.fileName());
        } else {
            xml->writeAttribute("texture", fInfo.canonicalFilePath());
        }
    }
    xml->writeEndElement();
}

void Entity::load(QXmlStreamReader *xml)
{
    setPosX(xml->attributes().value("x").toString().toInt());
    setPosY(xml->attributes().value("y").toString().toInt());
    setPosZ(xml->attributes().value("z").toString().toInt());
    setTexX(xml->attributes().value("tx").toString().toFloat());
    setTexY(xml->attributes().value("ty").toString().toFloat());
    setAngle(xml->attributes().value("angle").toString().toInt());
    setWidth(xml->attributes().value("width").toString().toInt());
    setHeight(xml->attributes().value("height").toString().toInt());

    pixmap = TexturesManager::getInstance()->getTexture(xml->attributes().value("texture").toString());

    xml->skipCurrentElement();
    xml->readNext();
}
