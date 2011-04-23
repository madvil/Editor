#include "background.h"
#include "constants.h"
#include "propertymanagers.h"
#include "texturesmanager.h"

Background::Background(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(BACKGROUND_NAME);
    init();

    sliding = 0;
    bgColor = QBrush(QColor(100, 130, 200));
    bgTexture = QBrush(QColor(0, 0, 0));

    name->setEnabled(false);
    topBorder = addNewProperty("Top border (%)", PropertyManagers::getInstance()->getIntPropertyManager());
    bottomBorder = addNewProperty("Bottom border (%)", PropertyManagers::getInstance()->getIntPropertyManager());
    opacity = addNewProperty("Opacity", PropertyManagers::getInstance()->getDoublePropertyManager());

    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(topBorder, 0, 1000);
    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(bottomBorder, 0, 1000);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setRange(opacity, 0, 1);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(opacity, 0.1);

    setTopBorder(100);
    setBottomBorder(100);
    setOpacity(0);
}

void Background::paint(QPainter *painter, QPaintEvent *event)
{
    painter->save();
    painter->translate(-sliding, 0);

    float p = (float)getTopBorder() / 100.0;
    float p2 = (float)getBottomBorder() / 100.0;
    int h = (int)(((float)event->rect().height() / 3) * p);
    int h2 = (int)(((float)event->rect().height() / 3) * p2);
    painter->setOpacity(getOpacity());
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

void Background::setOpacity(float opacity)
{
    PropertyManagers::getInstance()->getDoublePropertyManager()->setValue(this->opacity, opacity);
}

void Background::save(QXmlStreamWriter *xml, bool toExport)
{
    xml->writeStartElement("background");
    {
        xml->writeAttribute("top_border", topBorder->valueText());
        xml->writeAttribute("bottom_border", bottomBorder->valueText());
        xml->writeAttribute("opacity", opacity->valueText());
    }
    xml->writeEndElement();
}

void Background::load(QXmlStreamReader *xml)
{

}
