#include <QImage>
#include "background.h"
#include "constants.h"
#include "propertymanagers.h"

Background::Background(QtAbstractPropertyBrowser *propertyBrowser)
    : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(BACKGROUND_NAME);
    init();

    sliding = 0;
    bgColor = QBrush(QColor(100, 130, 200));
    bgTexture = QBrush(QImage(":/textures/media/none.png"));

    name->setEnabled(false);
    topBorder = addNewProperty("Top border (%)", PropertyManagers::getInstance()->getIntPropertyManager());
    bottomBorder = addNewProperty("Bottom border (%)", PropertyManagers::getInstance()->getIntPropertyManager());

    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(topBorder, 0, 1000);
    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(bottomBorder, 0, 1000);

    setTopBorder(100);
    setBottomBorder(0);
}

void Background::paint(QPainter *painter, QPaintEvent *event)
{
    painter->save();
    painter->translate(-sliding, 0);

    float p = (float)getTopBorder() / 100.0;
    float p2 = (float)getBottomBorder() / 100.0;
    int h = (int)(((float)event->rect().height() / 3) * p);
    int h2 = (int)(((float)event->rect().height() / 2) * p2);
    painter->fillRect(QRect(0, (event->rect().height() / 2) - h, event->rect().width(), h + h2), bgTexture);

    painter->restore();
}

void Background::setTopBorder(int topBorder)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->topBorder, topBorder);
}

void Background::setBottomBorder(int bottomBorder)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->bottomBorder, bottomBorder);
}
