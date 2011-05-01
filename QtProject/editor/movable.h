#ifndef MOVABLE_H
#define MOVABLE_H

#include "baseobject.h"

class Scene;

class Movable: public BaseObject
{
    Q_OBJECT
public:
    Movable(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) {}

    void translate(int dX, int dY);

    void setPosX(int posX);
    int getPosX() const { return posX->valueText().toInt(); }

    void setPosY(int posY);
    int getPosY() const { return posY->valueText().toInt(); }

    void setPosZ(int posZ);
    int getPosZ() const { return posZ->valueText().toFloat(); }

    void setAngle(int angle);
    int getAngle() const { return angle->valueText().toInt(); }

    void setWidth(int width);
    int getWidth() const { return width->valueText().toInt(); }

    void setHeight(int height);
    int getHeight() const { return height->valueText().toInt(); }

    void setCheckedCorner(bool checkedCorner) { this->checkedCorner = checkedCorner; }
    bool isCheckedCorner() const { return checkedCorner; }
    bool checkCorner(int w_x, int w_y, Scene *scene);

    virtual void save(QXmlStreamWriter *xml, bool toExport) {}
    virtual void load(QXmlStreamReader *xml) {}

protected:
    QtProperty *posX;
    QtProperty *posY;
    QtProperty *posZ;
    QtProperty *angle;
    QtProperty *width;
    QtProperty *height;

    bool checkedCorner;
};

#endif // MOVABLE_H
