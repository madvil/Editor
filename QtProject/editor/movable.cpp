#include "movable.h"
#include "propertymanagers.h"
#include "scene.h"

Movable::Movable(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    checkedCorner = false;

    posX = addNewProperty("X", PropertyManagers::getInstance()->getIntPropertyManager());
    posY = addNewProperty("Y", PropertyManagers::getInstance()->getIntPropertyManager());
    posZ = addNewProperty("Z", PropertyManagers::getInstance()->getIntPropertyManager());
    angle = addNewProperty("Angle", PropertyManagers::getInstance()->getIntPropertyManager());
    width = addNewProperty("Width", PropertyManagers::getInstance()->getIntPropertyManager());
    height = addNewProperty("Height", PropertyManagers::getInstance()->getIntPropertyManager());
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

void Movable::setAngle(int angle)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->angle, angle);
}

void Movable::setWidth(int width)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->width, width);
}

void Movable::setHeight(int height)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->height, height);
}

bool Movable::checkCorner(int w_x, int w_y, Scene *scene)
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
