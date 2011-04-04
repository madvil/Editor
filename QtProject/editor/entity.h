#ifndef ENTITY_H
#define ENTITY_H

#include "baseobject.h"

class QPainter;
class QPaintEvent;

class Entity : public BaseObject
{
    Q_OBJECT
public:
    Entity(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) { }

    void setPosX(int posX);
    int getPosX() const { return posX->valueText().toInt(); }

    void setPosY(int posY);
    int getPosY() const { return posY->valueText().toInt(); }

    void setPosZ(int posZ);
    int getPosZ() const { return posZ->valueText().toFloat(); }

    void setScaleX(float scX);
    float getScaleX() const { return scX->valueText().toFloat(); }

    void setScaleY(float scY);
    float getScaleY() const { return scY->valueText().toFloat(); }

    void setAngle(int angle);
    int getAngle() const { return angle->valueText().toInt(); }

    void setWidth(int width);
    int getWidth() const { return width->valueText().toInt(); }

    void setHeight(int height);
    int getHeight() const { return height->valueText().toInt(); }

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }

protected:
    QtProperty *geometryGroup;
    QtProperty *posX;
    QtProperty *posY;
    QtProperty *posZ;
    QtProperty *scX;
    QtProperty *scY;
    QtProperty *angle;
    QtProperty *width;
    QtProperty *height;
};

#endif // ENTITY_H
