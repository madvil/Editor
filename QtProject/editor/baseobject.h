#ifndef BASEOBJECT_H
#define BASEOBJECT_H

#include <QtCore>
#include "qtpropertybrowser/qtpropertybrowser.h"

class BaseObject : public QObject
{
    Q_OBJECT

public:
    BaseObject(QtAbstractPropertyBrowser *propertyBrowser);
    ~BaseObject();

    void setRootName(QString name);
    QString getRootName() const { return rootProperty->propertyName(); }
    QtProperty *getRootProperty() const {  return rootProperty; }

    QtProperty *addNewProperty(QString propertyName, QtAbstractPropertyManager *propertyManager, QtProperty *parent = 0);
    QString getPropertyValue(QString propertyName);

    void setName(QString name);
    QString getName() const { return name->valueText(); }

    void setSelected(bool selected);
    bool isSelected() const { return selected; }

    void setTag(int tag);
    int getTag() const { return tag; }

    virtual void save(QDataStream *ds) = 0;
    virtual void load(QDataStream *ds) = 0;

protected:
    QtAbstractPropertyBrowser *propertyBrowser;
    QtProperty *rootProperty;
    QtProperty *name;
    QMap<QString, QtProperty *> properties;

    bool selected;
    int tag;
};

#endif // BASEOBJECT_H
