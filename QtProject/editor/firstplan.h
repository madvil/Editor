#ifndef FIRSTPLAN_H
#define FIRSTPLAN_H

#include "baseobject.h"

class Scene;
class QPainter;
class QPaintEvent;

class Firstplan : public BaseObject
{
    Q_OBJECT
public:
    Firstplan(QtAbstractPropertyBrowser *propertyBrowser, Scene *scene);

    void paint(QPainter *painter, QPaintEvent *event);

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }

protected:
    Scene *scene;

};

#endif // FIRSTPLAN_H