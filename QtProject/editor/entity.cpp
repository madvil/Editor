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
    scX = addNewProperty("Scale X", PropertyManagers::getInstance()->getDoublePropertyManager(), geometryGroup);
    scY = addNewProperty("Scale Y", PropertyManagers::getInstance()->getDoublePropertyManager(), geometryGroup);
    angle = addNewProperty("Angle", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    width = addNewProperty("Width", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);
    height = addNewProperty("Height", PropertyManagers::getInstance()->getIntPropertyManager(), geometryGroup);

    scX->setEnabled(false);
    scY->setEnabled(false);
    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(angle, 0, 360);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(scX, 0.1);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(scY, 0.1);

    setScaleX(1.0);
    setScaleY(1.0);
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
        painter->drawPixmap(x, y, w, h, *pixmap);

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
