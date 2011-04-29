#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "baseobject.h"
#include "QPen"

class Scene;

class Landscape : public BaseObject
{
    Q_OBJECT
public:
    Landscape(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) {}
    void paint(QPainter *painter, QPaintEvent *event, Scene *scene);

    void setLeft(int left);
    int getLeft() const { return left->valueText().toInt(); }

    void setRight(int right);
    int getRight() const { return right->valueText().toInt(); }

    void setHeight(int height);
    int getHeight() const { return height->valueText().toInt(); }

    virtual void save(QXmlStreamWriter *xml, bool toExport) {}
    virtual void load(QXmlStreamReader *xml) {}

protected:
    QtProperty *group;
    QtProperty *left;
    QtProperty *right;
    QtProperty *height;

    QPen green;
};

#endif // LANDSCAPE_H
