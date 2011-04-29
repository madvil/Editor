#include "landscape.h"
#include "propertymanagers.h"
#include "constants.h"
#include "scene.h"

Landscape::Landscape(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(LANSCAPE_NAME);
    init();

    green = QPen(QColor(0, 255, 0));

    name->setEnabled(false);
    group = addNewProperty("Borders", PropertyManagers::getInstance()->getGroupPropertyManager());
    left = addNewProperty("Left (screens)", PropertyManagers::getInstance()->getIntPropertyManager(), group);
    right = addNewProperty("Right (screens)", PropertyManagers::getInstance()->getIntPropertyManager(), group);
    height = addNewProperty("Height (%)", PropertyManagers::getInstance()->getIntPropertyManager(), group);

    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(height, 0, 100);

    setLeft(0);
    setRight(1);
    setHeight(50);
}

void Landscape::paint(QPainter *painter, QPaintEvent *event, Scene *scene)
{
    int w_h = scene->getWorldHeight() * scene->getRatio();
    int w_w = (float)w_h * ((float)scene->getTDWidth() / (float)scene->getTDHeight());
    int h = w_h * ((float)getHeight() / 100.f);
    int d_h = event->rect().bottom() / 6;
    painter->setPen(green);
    painter->drawRect(getLeft() * w_w, d_h * 5 - h, getRight() * w_w, h);
}

void Landscape::setLeft(int left)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->left, left);
}

void Landscape::setRight(int right)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->right, right);
}

void Landscape::setHeight(int height)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->height, height);
}
