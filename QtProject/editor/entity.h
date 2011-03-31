#ifndef ENTITY_H
#define ENTITY_H

#include "baseobject.h"

class Entity : public BaseObject
{
    Q_OBJECT
public:
    Entity(QtAbstractPropertyBrowser *propertyBrowser);

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }
};

#endif // ENTITY_H
