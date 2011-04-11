#ifndef ENTITY_H
#define ENTITY_H

#include "baseobject.h"

class QPainter;
class QPaintEvent;
class Scene;

class Entity : public BaseObject
{
    Q_OBJECT
public:
    Entity(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) {}
    void paint(QPainter *painter, QPaintEvent *event, Scene *scene);

    void translate(int dX, int dY);

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

    void setDrawRect(bool drawRect) { this->drawRect = drawRect; }

    void setCheckedCorner(bool checkedCorner) { this->checkedCorner = checkedCorner; }
    bool isCheckedCorner() const { return checkedCorner; }
    bool checkCorner(int w_x, int w_y, Scene *scene);

    void setPixmap(QPixmap *pixmap) { this->pixmap = pixmap; }
    QPixmap *getPixmap() { return pixmap; }

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

    QPixmap *pixmap;
    bool checkedCorner;
    bool drawRect;
};

#endif // ENTITY_H
