#include "firstplan.h"
#include "constants.h"
#include "scene.h"

Firstplan::Firstplan(QtAbstractPropertyBrowser *propertyBrowser, Scene *scene) : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(FIRSTPLAN_NAME);
    init();
}

void Firstplan::paint(QPainter *painter, QPaintEvent *event)
{

}

void Firstplan::save(QXmlStreamWriter *xml, bool toExport)
{
    xml->writeStartElement("firstplan");
    {

    }
    xml->writeEndElement();
}

void Firstplan::load(QXmlStreamReader *xml)
{
    xml->skipCurrentElement();
    xml->readNext();
}
