#ifndef BACKGROUND_H
#define BACKGROUND_H

#include <QBrush>
#include "baseobject.h"

class QPainter;
class QPaintEvent;

class Background : public BaseObject
{
    Q_OBJECT
public:
    Background(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event);

    QBrush *getBgColor() { return &bgColor; }

    void setTopBorder(int topBorder);
    int getTopBorder() const { return topBorder->valueText().toInt(); }

    void setBottomBorder(int bottomBorder);
    int getBottomBorder() const { return bottomBorder->valueText().toInt(); }

    void setOpacity(float opacity);
    float getOpacity() const { return opacity->valueText().toFloat(); }

    void setSliding(int sliding) { this->sliding = sliding; }

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }

protected:
    QBrush bgColor;
    QBrush bgTexture;
    QtProperty *topBorder;
    QtProperty *bottomBorder;
    QtProperty *opacity;
    int sliding;
    bool fixed;
};

#endif // BACKGROUND_H
