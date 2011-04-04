#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QObject>
#include <QPainter>
#include <QPaintEvent>

class Entity;

class Transformer : public QObject
{
    Q_OBJECT
public:
    explicit Transformer(QObject *parent = 0);
    void paint(QPainter *painter, QPaintEvent *event);
    void assignTo(Entity *entity);

protected:
    Entity *assignedEntity;

signals:

public slots:

};

#endif // TRANSFORMER_H
