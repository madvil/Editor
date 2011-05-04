#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QBrush>
#include "baseobject.h"
#include "simpletexture.h"

class Scene;
class QPainter;
class QPaintEvent;

class Background : public BaseObject
{
    Q_OBJECT
public:
    Background(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) { }
    void paint(QPainter *painter, QPaintEvent *event, Scene *scene);

    QBrush *getBgColor();
    void setBgColor(QColor color);

    void setTopBorder(int topBorder);
    int getTopBorder() const { return topBorder->valueText().toInt(); }

    void setBottomBorder(int bottomBorder);
    int getBottomBorder() const { return bottomBorder->valueText().toInt(); }

    void setLeftBorder(int leftBorder);
    int getLeftBorder() const { return leftBorder->valueText().toInt(); }

    void setRightBorder(int rightBorder);
    int getRightBorder() const { return rightBorder->valueText().toInt(); }

    void setOpacity(float opacity);
    float getOpacity() const { return opacity->valueText().toFloat(); }

    void setSliding(int sliding) { this->sliding = sliding; }

    void setTexture(SimpleTexture *tex) { this->tex = tex; }

    virtual void save(QXmlStreamWriter *xml, bool toExport);
    virtual void load(QXmlStreamReader *xml);

protected:
    QBrush bgColor;
    SimpleTexture *tex;
    QtProperty *topBorder;
    QtProperty *bottomBorder;
    QtProperty *leftBorder;
    QtProperty *rightBorder;
    QtProperty *opacity;
    QtProperty *color;
    QtProperty *onlyInFirstScreen;
    int sliding;
    bool fixed;
};

#endif // BACKGROUND_H
