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

    void setLeftBorder(int leftBorder);
    int getLeftBorder() const { return leftBorder->valueText().toInt(); }

    void setRightBorder(int rightBorder);
    int getRightBorder() const { return rightBorder->valueText().toInt(); }

    void setOpacity(float opacity);
    float getOpacity() const { return opacity->valueText().toFloat(); }

    void setSliding(int sliding) { this->sliding = sliding; }

    virtual void save(QXmlStreamWriter *xml, bool toExport);
    virtual void load(QXmlStreamReader *xml);

protected:
    QBrush bgColor;
    QBrush bgTexture;
    QtProperty *topBorder;
    QtProperty *bottomBorder;
    QtProperty *leftBorder;
    QtProperty *rightBorder;
    QtProperty *opacity;
    int sliding;
    bool fixed;
};

#endif // BACKGROUND_H
