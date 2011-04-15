#include "baseobject.h"
#include "propertymanagers.h"
#include "constants.h"
#include "editortreewidgetmanager.h"

BaseObject::BaseObject(QtAbstractPropertyBrowser *propertyBrowser) : QObject(propertyBrowser)
{
    tag = 0;
    assignedItem = 0;
    selected = false;
    this->propertyBrowser = propertyBrowser;
    rootProperty = PropertyManagers::getInstance()->getGroupPropertyManager()->addProperty("root");
    name = addNewProperty("Name", PropertyManagers::getInstance()->getStringPropertyManager());

    setRootName(UNKNOWN);
    setName(DEFAULT_NAME);    
}

BaseObject::~BaseObject()
{

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
    if (selected) {
        propertyBrowser->addProperty(rootProperty);
    } else {
        propertyBrowser->removeProperty(rootProperty);
    }

    this->selected = selected;
}

void BaseObject::setTag(int tag)
{
    this->tag = tag;
}

void BaseObject::select()
{
    propertyBrowser->clear();
    EditorTreeWidgetManager::getInstance()->select(assignedItem);
}
