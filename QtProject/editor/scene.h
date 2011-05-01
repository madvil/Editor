#ifndef SCENE_H
#define SCENE_H

#include <QVector>
#include <QBrush>
#include <QFont>
#include <QPen>
#include "background.h"
#include "firstplan.h"
#include "landscape.h"
#include "entity.h"
#include "transformer.h"
#include "movable.h"
#include "simpletexture.h"

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

    Landscape *getLandscape() const { return landscape; }

    virtual void save(QXmlStreamWriter *xml, bool toExport);
    virtual void load(QXmlStreamReader *xml);

    int convertWindowCoordToWorld(int w_y);
    int convertWorldCoordToWindow(int y);
    float getRatio();

    Entity *addEntity(Entity *entity);
    Entity *addEntity(SimpleTexture *st);
    Entity *addEntity(int x, int y, int width, int height);

    Entity *getEntity(int w_x, int w_y);
    Movable *getMovable(int w_x, int w_y);

    void startModifyMovable(Movable *m);
    void translateMovable(int dX, int dY);
    void transformMovable(int dX, int dY);
    void endModifyMovable();

protected:
    QtProperty *targetDeviceGroup;
    QtProperty *tdHeight;
    QtProperty *tdWidth;
    QtProperty *worldHeight;

    Background *background;
    Firstplan *firstplan;
    Landscape *landscape;
    QVector<Entity *> paintObjects;
    Transformer *transformer;
    QBrush transparentBlack;
    QPen debugPen;

    Movable *translatingMovable;
    int translateX;
    int translateY;
    int startPosX;
    int startPosY;
    int startWidth;
    int startHeight;
    int lastHeight;

    bool drawDebugInfo;
    int sliding;
    int animSliding;

    void loadEntry(QXmlStreamReader *xml);

signals:

};

#endif // SCENE_H
