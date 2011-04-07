#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QObject>
#include <QPainter>
#include <QPaintEvent>
#include <QPen>
#include "entity.h"

class Transformer : public QObject
{
    Q_OBJECT
public:
    explicit Transformer(QObject *parent = 0);
    void paint(QPainter *painter, QPaintEvent *event, int sliding);
    void assignTo(Entity *entity);

protected:
    Entity *assignedEntity;
    QPen redPen;

signals:

public slots:

};

#endif // TRANSFORMER_H
