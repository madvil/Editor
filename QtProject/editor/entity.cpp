#include "entity.h"
#include "constants.h"
#include "propertymanagers.h"
#include "scene.h"
#include "texturesmanager.h"
#include "qgl.h"

static int ENTITY_COUNTER = 1;

Entity::Entity(QtAbstractPropertyBrowser *propertyBrowser) : Movable(propertyBrowser)
{
    setRootName(ENTITY_GROUP);
    setName(tr("Entity ") + QString::number(ENTITY_COUNTER++));
    init();
    drawRect = false;
    tex = 0;

    tX = addNewProperty("Texture X", PropertyManagers::getInstance()->getDoublePropertyManager());
    tY = addNewProperty("Texture Y", PropertyManagers::getInstance()->getDoublePropertyManager());

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
    int z = getPosZ();
    int w = getWidth() * ratio;
    int h = getHeight() * ratio;
    if (tex == 0)
        tex = TexturesManager::getInstance()->getNone();

    if (!((x - scene->getSlide() < 0 || x - scene->getSlide() > event->rect().width()) &&
                       (x + w - scene->getSlide() < 0 || x + w - scene->getSlide() > event->rect().width()))) {
        painter->beginNativePainting();
        {
            float _x = getTexX();
            float _y = getTexY();

            float coords[12] =
            {
                x,     y,     z,
                x + w, y,     z,
                x + w, y + h, z,
                x    , y + h, z,
            };

            float t_coords[8] =
            {
                0.0, 0.0,
                _x,  0.0,
                _x,  _y,
                0.0, _y
            };

            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glColor3f(1.0, 1.0, 1.0);

            if (tex != 0) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, tex->id);

                glColor4f(1.0, 1.0, 1.0, 1.0);
            }

            glTexCoordPointer(2, GL_FLOAT, 0, t_coords);
            glVertexPointer(3, GL_FLOAT, 0, coords);
            glDrawArrays(GL_QUADS, 0, 4);

            glDisable(GL_TEXTURE_2D);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
        painter->endNativePainting();

        if (!selected && drawRect)
            painter->drawRect(x, y, w, h);
    }
}

void Entity::setTexX(float tX)
{
    PropertyManagers::getInstance()->getDoublePropertyManager()->setValue(this->tX, tX);
}

void Entity::setTexY(float tY)
{
    PropertyManagers::getInstance()->getDoublePropertyManager()->setValue(this->tY, tY);
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

        QFileInfo fInfo(tex->path);
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

    tex = TexturesManager::getInstance()->getTexture(xml->attributes().value("texture").toString());

    xml->skipCurrentElement();
    xml->readNext();
}
