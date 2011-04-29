#include "movable.h"
#include "propertymanagers.h"

Movable::Movable(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    posX = addNewProperty("X", PropertyManagers::getInstance()->getIntPropertyManager());
    posY = addNewProperty("Y", PropertyManagers::getInstance()->getIntPropertyManager());
    posZ = addNewProperty("Z", PropertyManagers::getInstance()->getIntPropertyManager());
}

void Movable::translate(int dX, int dY)
{
    setPosX(getPosX() - dX);
    setPosY(getPosY() - dY);
}

void Movable::setPosX(int posX)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->posX, posX);
}

void Movable::setPosY(int posY)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->posY, posY);
}

void Movable::setPosZ(int posZ)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->posZ, posZ);
}
