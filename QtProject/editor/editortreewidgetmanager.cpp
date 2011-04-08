#include "editortreewidgetmanager.h"

static EditorTreeWidgetManager *singletone;
static QList<EditorTreeWidgetItem *> rootItems;
static bool firstSelect = true;

EditorTreeWidgetManager::EditorTreeWidgetManager(QTreeWidget *parent, QtAbstractPropertyBrowser *propertyBrowser)
    : QObject(parent)
{
    this->parent = parent;
    this->propertyBrowser = propertyBrowser;
    singletone = this;
    lastSelected = 0;
}

EditorTreeWidgetManager *EditorTreeWidgetManager::getInstance()
{
    return singletone;
}

void EditorTreeWidgetManager::updateNames()
{
    if (lastSelected != 0 && lastSelected->getAssignedObject() != 0)
        lastSelected->getAssignedObject()->updateName();
}

void EditorTreeWidgetManager::addNewObject(BaseObject *object)
{
    EditorTreeWidgetItem *parentItem = 0;
    bool resultOk = false;
    for (int i = 0; i < rootItems.count(); i++) {
        parentItem = rootItems.at(i);
        if (parentItem->isRoot() && parentItem->getName().compare(object->getRootName()) == 0) {
            resultOk = true;
            break;
        }
    }

    if (!resultOk) {
        parentItem = new EditorTreeWidgetItem(parent);
        parentItem->setName(object->getRootName());
        parentItem->setIsRoot(true);
        rootItems << parentItem;
    }

    EditorTreeWidgetItem *newItem = new EditorTreeWidgetItem(parentItem);
    newItem->setName(object->getName());
    newItem->assignObject(object);
    object->assignEditorTreeWidgetItem(newItem);
}

void EditorTreeWidgetManager::select(EditorTreeWidgetItem *item)
{
    deselect();
    firstSelect = false;
    lastSelected = item;

    if (lastSelected != 0 && lastSelected->getAssignedObject() != 0)
        lastSelected->getAssignedObject()->setSelected(true);
}

void EditorTreeWidgetManager::deselect()
{
    if (!firstSelect && lastSelected != 0 && lastSelected->getAssignedObject() != 0)
        lastSelected->getAssignedObject()->setSelected(false);
}
