#ifndef MOVER_H
#define MOVER_H

#include "movable.h"

class Scene;

class Mover : public Movable
{
    Q_OBJECT
public:
    Mover(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) {}
    void paint(QPainter *painter, QPaintEvent *event, Scene *scene);

    bool isCheckedCorner() { return false; }
    bool checkCorner(int w_x, int w_y, Scene *scene) { return false; }
    bool check(int w_x, int w_y, Scene *scene);

protected:
    QBrush darkRed;
    QPen green;
    QPen red;
};

#endif // MOVER_H
