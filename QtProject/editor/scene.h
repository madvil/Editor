#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QBrush>
#include <QFont>
#include <QPen>
#include "background.h"

class QPainter;
class QPaintEvent;

class Scene : public BaseObject
{
    Q_OBJECT
public:
    explicit Scene(QtAbstractPropertyBrowser *propertyBrowser);
    void paint(QPainter *painter, QPaintEvent *event);
    bool animate(); //true whet animate ended

    void setDrawDebugInfo(bool val) { drawDebugInfo = val; }
    void slide(int slideDelta) { sliding += slideDelta; if (sliding < 0) sliding = 0; }
    int getSlide() { return sliding; }
    void animationSlide(int animSliding) { this->animSliding = animSliding; }

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }

protected:
    Background *background;
    QVector<BaseObject *> paintObjects;
    QBrush transparentBlack;
    QPen debugPen;
    bool drawDebugInfo;
    int sliding;
    int animSliding;

signals:

};

#endif // SCENE_H
