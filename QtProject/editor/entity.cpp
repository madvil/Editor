#include "entity.h"
#include "constants.h"
#include "propertymanagers.h"

Entity::Entity(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    qDebug() << "Entity" << 1;
    setRootName(ENTITY_GROUP);
    qDebug() << "Entity" << 2;
    init();
    qDebug() << "Entity" << 3;

    geometryGroup = addNewProperty("Geometry", PropertyManagers::getInstance()->getGroupPropertyManager());
    posX = addNewProperty("X", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    posY = addNewProperty("Y", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    posY = addNewProperty("Z", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    scX = addNewProperty("Scale X", PropertyManagers::getInstance()->getDoublePropertyManager(), geometryGroup);
    scY = addNewProperty("Scale Y", PropertyManagers::getInstance()->getDoublePropertyManager(), geometryGroup);
    angle = addNewProperty("Angle", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    width = addNewProperty("Width", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    height = addNewProperty("Height", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);

    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(angle, 0, 360);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(scX, 0.1);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(scY, 0.1);

    setScaleX(1.0);
    setScaleY(1.0);
}

void Entity::paint(QPainter *painter, QPaintEvent *event)
{
    painter->drawRect(getPosX(), getPosY(), getWidth(), getHeight());
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

void Entity::setScaleX(float scX)
{
    PropertyManagers::getInstance()->getDoublePropertyManager()->setValue(this->scX, scX);
}

void Entity::setScaleY(float scY)
{
    PropertyManagers::getInstance()->getDoublePropertyManager()->setValue(this->scY, scY);
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
