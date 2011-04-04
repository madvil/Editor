#ifndef TRANSFORMER_H
#define TRANSFORMER_H

#include <QObject>

class Entity;

class Transformer : public QObject
{
    Q_OBJECT
public:
    explicit Transformer(QObject *parent = 0);

    void assignTo(Entity *entity);

protected:
    Entity *assignedEntity;

signals:

public slots:

};

#endif // TRANSFORMER_H
