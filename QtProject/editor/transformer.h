#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include "movable.h"

class Scene;

class Transformer : public QObject
{
    Q_OBJECT
public:
    explicit Transformer(QObject *parent);
    void paint(QPainter *painter, QPaintEvent *event, bool drawResizeRect = true, bool drawSize = true);
    void assignTo(Movable *m);

protected:
    Scene *scene;
    Movable *assignedMovable;
    QPen redPen;
    QPen whitePen;

signals:

public slots:

};

#endif // TRANSFORMER_H
