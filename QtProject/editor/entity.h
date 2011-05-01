#ifndef ENTITY_H
#define ENTITY_H

#include "movable.h"
#include "simpletexture.h"

class QPainter;
class QPaintEvent;
class Scene;

class Entity : public Movable
{
    Q_OBJECT
public:
    Entity(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) {}
    void paint(QPainter *painter, QPaintEvent *event, Scene *scene);

    void setTexX(float tX);
    float getTexX() const { return tX->valueText().toFloat(); }

    void setTexY(float tY);
    float getTexY() const { return tY->valueText().toFloat(); }

    void setDrawRect(bool drawRect) { this->drawRect = drawRect; }

    void setTex(SimpleTexture *tex) { this->tex = tex; }
    SimpleTexture *getTex() { return tex; }

    virtual void save(QXmlStreamWriter *xml, bool toExport);
    virtual void load(QXmlStreamReader *xml);

protected:
    QtProperty *tX;
    QtProperty *tY;

    SimpleTexture *tex;
    bool drawRect;
};

#endif // ENTITY_H
