#include "baseobject.h"
#include "propertymanagers.h"
#include "constants.h"
#include "editortreewidgetmanager.h"

BaseObject::BaseObject(QtAbstractPropertyBrowser *propertyBrowser) : QObject(propertyBrowser)
{
    tag = 0;
    assignedItem = 0;
    heightRatio = 1.0;
    selected = false;
    this->propertyBrowser = propertyBrowser;
    rootProperty = PropertyManagers::getInstance()->getGroupPropertyManager()->addProperty("root");
    name = addNewProperty("Name", PropertyManagers::getInstance()->getStringPropertyManager());

    setRootName(UNKNOWN);
    setName(DEFAULT_NAME);    
}

void BaseObject::init()
{
    if (EditorTreeWidgetManager::getInstance() != 0)
        EditorTreeWidgetManager::getInstance()->addNewObject(this);
}

void BaseObject::setRootName(QString name)
{
    rootProperty->setPropertyName(name);
}

QtProperty *BaseObject::addNewProperty(QString propertyName,
                                       QtAbstractPropertyManager *propertyManager, QtProperty *parent)
{
    QtProperty *newProperty = propertyManager->addProperty(propertyName);
    properties[propertyName] = newProperty;

    if (parent == 0) {
        rootProperty->addSubProperty(newProperty);
    } else {
        parent->addSubProperty(newProperty);
    }

    return newProperty;
}

QString BaseObject::getPropertyValue(QString propertyName)
{
    return properties[propertyName]->valueText();
}

void BaseObject::setName(QString name)
{
    PropertyManagers::getInstance()->getStringPropertyManager()->setValue(this->name, name);
    updateName();
}

void BaseObject::updateName()
{
//    if (assignedItem != 0)
//        assignedItem->setName(getName());
}

void BaseObject::setSelected(bool selected)
{
    //bug here in release
    qDebug() << 1;
    if (selected) {
        qDebug() << 2;
        propertyBrowser->addProperty(rootProperty);
    } else {
        qDebug() << 3;
        if (propertyBrowser != 0) {
            qDebug() << 3.1;
            propertyBrowser->removeProperty(rootProperty);
            qDebug() << 3.2;
        }
    }
    qDebug() << 4;
    this->selected = selected;
    qDebug() << 4.1;
}

void BaseObject::setTag(int tag)
{
    this->tag = tag;
}
