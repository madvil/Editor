#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPixmap>
#include "background.h"
#include "entity.h"
#include "transformer.h"

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
    int getSlide() const { return sliding; }
    void animationSlide(int animSliding) { this->animSliding = animSliding; }

    void setTDHeight(int tdHeight);
    int getTDHeight() const { return tdHeight->valueText().toInt(); }

    void setTDWidth(int tdWidth);
    int getTDWidth() const { return tdWidth->valueText().toInt(); }

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }

    Entity *addEntity(Entity *entity);
    Entity *addEntity(QPixmap *pixmap);
    Entity *addEntity(int x, int y, int width, int height);

protected:
    QtProperty *targetDeviceGroup;
    QtProperty *tdHeight;
    QtProperty *tdWidth;

    Background *background;
    QVector<Entity *> paintObjects;
    Transformer *transformer;
    QBrush transparentBlack;
    QPen debugPen;

    bool drawDebugInfo;
    int sliding;
    int animSliding;

signals:

};

#endif // SCENE_H
