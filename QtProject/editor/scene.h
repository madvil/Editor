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
class GLWidget;

class Scene : public BaseObject
{
    Q_OBJECT
public:
    explicit Scene(QtAbstractPropertyBrowser *propertyBrowser);
    void paint(QPainter *painter, QPaintEvent *event) { }
    void paint(QPainter *painter, QPaintEvent *event, GLWidget *glWidget);
    bool animate(); //true whet animate ended

    void setDrawDebugInfo(bool val) { drawDebugInfo = val; }
    void slide(int slideDelta) { sliding += slideDelta; if (sliding < 0) sliding = 0; }
    int getSlide() const { return sliding; }
    void animationSlide(int animSliding) { this->animSliding = animSliding; }

    void setTDHeight(int tdHeight);
    int getTDHeight() const { return tdHeight->valueText().toInt(); }

    void setTDWidth(int tdWidth);
    int getTDWidth() const { return tdWidth->valueText().toInt(); }

    void setWorldHeight(int worldHeight);
    int getWorldHeight() const { return worldHeight->valueText().toInt(); }

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }

    int convertWindowCoordToWorld(int w_y, int height);
    int convertWorldCoordToWindow(int y, int height);
    float getRatio(int height);

    Entity *addEntity(Entity *entity);
    Entity *addEntity(QPixmap *pixmap);
    Entity *addEntity(int x, int y, int width, int height);

    Entity *getEntity(int w_x, int w_y, int height);
    Entity *select(int w_x, int w_y, int height);

    void startModifyEntity(Entity *e);
    void translateEntity(int dX, int dY, int height);
    void transformEntity(int dX, int dY, int height);
    void endModifyEntity();

protected:
    QtProperty *targetDeviceGroup;
    QtProperty *tdHeight;
    QtProperty *tdWidth;
    QtProperty *worldHeight;

    Background *background;
    QVector<Entity *> paintObjects;
    Transformer *transformer;
    QBrush transparentBlack;
    QPen debugPen;

    Entity *translatingEntity;
    int translateX;
    int translateY;
    int startPosX;
    int startPosY;
    int startWidth;
    int startHeight;

    bool drawDebugInfo;
    int sliding;
    int animSliding;

signals:

};

#endif // SCENE_H
