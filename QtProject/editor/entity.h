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

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }
};

#endif // ENTITY_H
