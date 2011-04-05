#include "editortreewidgetmanager.h"

static EditorTreeWidgetManager *singletone;

EditorTreeWidgetManager::EditorTreeWidgetManager(QTreeWidget *parent) : QObject(parent)
{
    this->parent = parent;
    singletone = this;
    lastSelected = 0;
}

EditorTreeWidgetManager *EditorTreeWidgetManager::getInstance()
{
    return singletone;
}

void EditorTreeWidgetManager::addNewObject(BaseObject *object)
{
    EditorTreeWidgetItem *parentItem = 0;
    bool resultOk = false;
    for (int i = 0; i < rootItems.size(); i++) {
        parentItem = rootItems.at(i);
        if (parentItem->getName().compare(object->getRootName()) == 0) {
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
    if (lastSelected != 0 && lastSelected->getAssignedObject() != 0)
        lastSelected->getAssignedObject()->setSelected(false);

    lastSelected = item;

    if (lastSelected != 0 && lastSelected->getAssignedObject() != 0)
        lastSelected->getAssignedObject()->setSelected(true);
}
