#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QtCore>
#include <QPainter>
#include <QPaintEvent>
#include "qtpropertybrowser/qtpropertybrowser.h"
#include "editortreewidgetitem.h"

class BaseObject : public QObject
{
    Q_OBJECT

public:
    BaseObject(QtAbstractPropertyBrowser *propertyBrowser);
    ~BaseObject();

    virtual void paint(QPainter *painter, QPaintEvent *event) = 0;

    void setRootName(QString name);
    QString getRootName() const { return rootProperty->propertyName(); }
    QtProperty *getRootProperty() const {  return rootProperty; }

    QtProperty *addNewProperty(QString propertyName, QtAbstractPropertyManager *propertyManager, QtProperty *parent = 0);
    QString getPropertyValue(QString propertyName);

    void setName(QString name);
    void updateName();
    QString getName() const { return name->valueText(); }

    void setSelected(bool selected);
    bool isSelected() const { return selected; }

    void setTag(int tag);
    int getTag() const { return tag; }

    void assignEditorTreeWidgetItem(EditorTreeWidgetItem *item) { assignedItem = item; }
    EditorTreeWidgetItem *getAssignedEditorTreeWidgetItem() const { return assignedItem; }

    void select();

    virtual void save(QXmlStreamWriter *ds, bool toExport) = 0;
    virtual void load(QXmlStreamReader *ds) = 0;

protected:
    QtAbstractPropertyBrowser *propertyBrowser;
    QtProperty *rootProperty;
    QtProperty *name;
    QMap<QString, QtProperty *> properties;
    EditorTreeWidgetItem *assignedItem;

    bool selected;
    int tag;

    void init();
};

#endif // BASEOBJECT_H
