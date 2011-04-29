#ifndef ENTITY_H
#define ENTITY_H

#include "movable.h"

class QPainter;
class QPaintEvent;
class Scene;

class Entity : public Movable
{
    Q_OBJECT
public:
    Entity(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) {}
    void paint(QPainter *painter, QPaintEvent *event, Scene *scene);

    void setTexX(float tX);
    float getTexX() const { return tX->valueText().toFloat(); }

    void setTexY(float tY);
    float getTexY() const { return tY->valueText().toFloat(); }

    void setAngle(int angle);
    int getAngle() const { return angle->valueText().toInt(); }

    void setWidth(int width);
    int getWidth() const { return width->valueText().toInt(); }

    void setHeight(int height);
    int getHeight() const { return height->valueText().toInt(); }

    void setDrawRect(bool drawRect) { this->drawRect = drawRect; }

    void setCheckedCorner(bool checkedCorner) { this->checkedCorner = checkedCorner; }
    bool isCheckedCorner() const { return checkedCorner; }
    bool checkCorner(int w_x, int w_y, Scene *scene);

    void setPixmap(QPixmap *pixmap) { this->pixmap = pixmap; }
    QPixmap *getPixmap() { return pixmap; }

    virtual void save(QXmlStreamWriter *xml, bool toExport);
    virtual void load(QXmlStreamReader *xml);

protected:
    QtProperty *tX;
    QtProperty *tY;
    QtProperty *angle;
    QtProperty *width;
    QtProperty *height;

    QPixmap *pixmap;
    bool checkedCorner;
    bool drawRect;
};

#endif // ENTITY_H
