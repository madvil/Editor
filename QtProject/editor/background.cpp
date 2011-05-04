#include "background.h"
#include "qgl.h"
#include "constants.h"
#include "propertymanagers.h"
#include "texturesmanager.h"
#include "scene.h"

Background::Background(QtAbstractPropertyBrowser *propertyBrowser) : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(BACKGROUND_NAME);
    init();

    tex = 0;
    sliding = 0;
    bgColor = QBrush(QColor(100, 130, 200));

    name->setEnabled(false);
    topBorder = addNewProperty("Top border (%)", PropertyManagers::getInstance()->getIntPropertyManager());
    bottomBorder = addNewProperty("Bottom border (%)", PropertyManagers::getInstance()->getIntPropertyManager());
    leftBorder = addNewProperty("Left border (%)", PropertyManagers::getInstance()->getIntPropertyManager());
    rightBorder = addNewProperty("Right border (%)", PropertyManagers::getInstance()->getIntPropertyManager());
    opacity = addNewProperty("Opacity", PropertyManagers::getInstance()->getDoublePropertyManager());
    color = addNewProperty("Color", PropertyManagers::getInstance()->getColorPropertyManager());
    onlyInFirstScreen = addNewProperty("Only in first screen", PropertyManagers::getInstance()->getBoolPropertyManager());

    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(topBorder, 0, 100);
    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(bottomBorder, 0, 100);
    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(leftBorder, 0, 100);
    PropertyManagers::getInstance()->getIntPropertyManager()->setRange(rightBorder, 0, 100);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setRange(opacity, 0, 1);
    PropertyManagers::getInstance()->getDoublePropertyManager()->setSingleStep(opacity, 0.1);

    setBgColor(QColor(100, 130, 200));
    setTopBorder(100);
    setBottomBorder(100);
    setLeftBorder(100);
    setRightBorder(100);
    setOpacity(0.5);
}

void Background::paint(QPainter *painter, QPaintEvent *event, Scene *scene)
{
    if (tex == 0)
        tex = TexturesManager::getInstance()->getNone();

    painter->beginNativePainting();
    {
        float _h = ((float)event->rect().bottom() * 2.0 / 3.0);
        float _w = _h * ((float)scene->getTDWidth() / (float)scene->getTDHeight());
        int _y = scene->convertWorldCoordToWindow(0);
        int x = (_w - _w * ((float)getLeftBorder() / 100.0)) / 2.0;
        int y = _y + (_h - _h * ((float)getTopBorder() / 100.0)) / 2.0;
        int w = _w - x - (_w - _w * ((float)getRightBorder() / 100.0)) / 2.0;
        int h = _h - (y - _y) - (_h - _h * ((float)getBottomBorder() / 100.0)) / 2.0;

        float coords[8] =
        {
            x,     y,
            x + w, y,
            x + w, y + h,
            x,     y + h,
        };

        static float t_coords[8] =
        {
            0.0, 0.0,
            1.0, 0.0,
            1.0, 1.0,
            0.0, 1.0
        };

        glPushMatrix();
        {
            glEnableClientState(GL_VERTEX_ARRAY);
            glEnableClientState(GL_TEXTURE_COORD_ARRAY);
            glColor3f(1.0, 1.0, 1.0);

            if (tex != 0) {
                glEnable(GL_BLEND);
                glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

                glEnable(GL_TEXTURE_2D);
                glBindTexture(GL_TEXTURE_2D, tex->id);

                glColor4f(1.0, 1.0, 1.0, getOpacity());
            }

            glTranslatef(-scene->getSlide(), 0.0, 0.0);

            glTexCoordPointer(2, GL_FLOAT, 0, t_coords);
            glVertexPointer(2, GL_FLOAT, 0, coords);
            glDrawArrays(GL_QUADS, 0, 4);

            glDisable(GL_TEXTURE_2D);
            glDisableClientState(GL_TEXTURE_COORD_ARRAY);
            glDisableClientState(GL_VERTEX_ARRAY);
        }
        glPopMatrix();
    }
    painter->endNativePainting();
}

QBrush *Background::getBgColor()
{
    bgColor.setColor(PropertyManagers::getInstance()->getColorPropertyManager()->value(color));
    return &bgColor;
}

void Background::setBgColor(QColor color)
{
    PropertyManagers::getInstance()->getColorPropertyManager()->setValue(this->color, color);
}

void Background::setTopBorder(int topBorder)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->topBorder, topBorder);
}

void Background::setBottomBorder(int bottomBorder)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->bottomBorder, bottomBorder);
}

void Background::setLeftBorder(int leftBorder)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->leftBorder, leftBorder);
}

void Background::setRightBorder(int rightBorder)
{
    PropertyManagers::getInstance()->getIntPropertyManager()->setValue(this->rightBorder, rightBorder);
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
        xml->writeAttribute("left_border", leftBorder->valueText());
        xml->writeAttribute("right_border", rightBorder->valueText());
        xml->writeAttribute("opacity", opacity->valueText());
        if (!toExport) {
            xml->writeAttribute("only_in_first_screen", onlyInFirstScreen->valueText());
        }

        QFileInfo fInfo(tex->path);
        if (toExport) {
            xml->writeAttribute("texture", fInfo.fileName());
        } else {
            xml->writeAttribute("texture", fInfo.canonicalFilePath());
        }
    }
    xml->writeEndElement();
}

void Background::load(QXmlStreamReader *xml)
{
    setBottomBorder(xml->attributes().value("top_border").toString().toInt());
    setTopBorder(xml->attributes().value("bottom_border").toString().toInt());
    setLeftBorder(xml->attributes().value("left_border").toString().toInt());
    setRightBorder(xml->attributes().value("right_border").toString().toInt());
    setOpacity(xml->attributes().value("opacity").toString().toFloat());
    tex = TexturesManager::getInstance()->getTexture(xml->attributes().value("texture").toString());
    if (xml->attributes().value("only_in_first_screen").toString() == "True") {
        PropertyManagers::getInstance()->getIntPropertyManager()->setValue(onlyInFirstScreen, true);
    } else {
        PropertyManagers::getInstance()->getIntPropertyManager()->setValue(onlyInFirstScreen, false);
    }

    xml->skipCurrentElement();
    xml->readNext();
}
