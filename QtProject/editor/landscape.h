#ifndef LANDSCAPE_H
#define LANDSCAPE_H

#include "baseobject.h"
#include "mover.h"
#include "simpletexture.h"

class Scene;

class Landscape : public BaseObject
{
    Q_OBJECT
public:
    Landscape(QtAbstractPropertyBrowser *propertyBrowser);

    void paint(QPainter *painter, QPaintEvent *event) {}
    void paint(QPainter *painter, QPaintEvent *event, Scene *scene);
    void paintFractures(QPainter *painter, QPaintEvent *event, Scene *scene);

    void setLeft(int left);
    int getLeft() const { return left->valueText().toInt(); }

    void setRight(int right);
    int getRight() const { return right->valueText().toInt(); }

    void setHeight(int height);
    int getHeight() const { return height->valueText().toInt(); }

    Mover *getMover(int w_x, int w_y);
    Mover *addMover(int w_x, int w_y);
    Mover *getSelectedMover() const { return lastSelected; }

    virtual void save(QXmlStreamWriter *xml, bool toExport);
    virtual void load(QXmlStreamReader *xml);

protected:
    Scene *scene;
    QtProperty *group;
    QtProperty *left;
    QtProperty *right;
    QtProperty *height;
    SimpleTexture *tex;
    int lastHeight;
    int worldHeight;
    Mover *lastSelected;
    double **coords;
    int lastSize;

    QList<Mover *> fractures;

private slots:
    void landscapeHeightChanged(QtProperty *property);
};

#endif // LANDSCAPE_H
