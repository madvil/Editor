#ifndef FIRSTPLAN_H
#define FIRSTPLAN_H

#include "baseobject.h"

class QPainter;
class QPaintEvent;

class Firstplan : public BaseObject
{
    Q_OBJECT
public:
    Firstplan(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event);

    virtual void save(QXmlStreamWriter *xml, bool toExport);
    virtual void load(QXmlStreamReader *xml);

protected:

};

#endif // FIRSTPLAN_H
