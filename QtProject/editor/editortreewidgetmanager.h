#ifndef EDITORTREEWIDGETMANAGER_H
#define EDITORTREEWIDGETMANAGER_H

#include <QObject>
#include <QTreeWidget>
#include <QList>
#include "baseobject.h"
#include "editortreewidgetitem.h"
#include "qtpropertybrowser/qtpropertybrowser.h"

class EditorTreeWidgetManager : public QObject
{
    Q_OBJECT
public:
    explicit EditorTreeWidgetManager(QTreeWidget *parent, QtAbstractPropertyBrowser *propertyBrowser);

    static EditorTreeWidgetManager *getInstance();

    void updateNames();
    void addNewObject(BaseObject *object, bool visible = true);
    void select(EditorTreeWidgetItem *item);
    void deselect();
    void reset();
    void clear();

    EditorTreeWidgetItem *getSelected() const { return lastSelected; }

protected:
    QtAbstractPropertyBrowser *propertyBrowser;
    EditorTreeWidgetItem *lastSelected;

signals:

public slots:

};

#endif // EDITORTREEWIDGETMANAGER_H
