#ifndef EDITORTREEWIDGETMANAGER_H
#define EDITORTREEWIDGETMANAGER_H

#include <QObject>
#include <QTreeWidget>
#include <QVector>
#include "baseobject.h"
#include "editortreewidgetitem.h"

class EditorTreeWidgetManager : public QObject
{
    Q_OBJECT
public:
    explicit EditorTreeWidgetManager(QTreeWidget *parent = 0);

    static EditorTreeWidgetManager *getInstance();

    void addNewObject(BaseObject *object);
    void select(EditorTreeWidgetItem *item);

protected:
    QTreeWidget *parent;
    EditorTreeWidgetItem *lastSelected;
    QVector<EditorTreeWidgetItem *> rootItems;

signals:

public slots:

};

#endif // EDITORTREEWIDGETMANAGER_H
