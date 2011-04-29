#ifndef MOVABLE_H
#define MOVABLE_H

#include "baseobject.h"

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

    virtual void save(QXmlStreamWriter *xml, bool toExport) {}
    virtual void load(QXmlStreamReader *xml) {}

protected:
    QtProperty *posX;
    QtProperty *posY;
    QtProperty *posZ;
};

#endif // MOVABLE_H
