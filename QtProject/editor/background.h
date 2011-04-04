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

    virtual void save(QDataStream *ds) { }
    virtual void load(QDataStream *ds) { }

protected:
    QBrush bgColor;
    QtProperty *topBorder;
    QtProperty *bottomBorder;
    int sliding;
};

#endif // BACKGROUND_H
