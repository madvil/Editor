#include "editortreewidgetmanager.h"

static EditorTreeWidgetManager *singletone;
static QList<EditorTreeWidgetItem *> rootItems;
static bool firstSelect = true;
static QTreeWidget *s_parent;

EditorTreeWidgetManager::EditorTreeWidgetManager(QTreeWidget *parent, QtAbstractPropertyBrowser *propertyBrowser)
    : QObject(parent)
{
    s_parent = parent;
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

void EditorTreeWidgetManager::addNewObject(BaseObject *object, bool visible)
{
    if (!visible) {
        EditorTreeWidgetItem *newItem = new EditorTreeWidgetItem;
        newItem->setName(object->getName());
        newItem->assignObject(object);
        object->assignEditorTreeWidgetItem(newItem);
        return;
    }

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
        parentItem = new EditorTreeWidgetItem(s_parent);
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

    updateNames();
}

void EditorTreeWidgetManager::deselect()
{
    if (!firstSelect && lastSelected != 0 && lastSelected->getAssignedObject() != 0)
        lastSelected->getAssignedObject()->setSelected(false);
}

void EditorTreeWidgetManager::reset()
{
    lastSelected = 0;
}

void EditorTreeWidgetManager::clear()
{
    rootItems.clear();
    reset();
}
