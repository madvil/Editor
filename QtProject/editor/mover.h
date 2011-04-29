#ifndef MOVER_H
#define MOVER_H

#include "movable.h"

class Mover : public Movable
{
    Q_OBJECT
public:
    Mover(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event);
};

#endif // MOVER_H
