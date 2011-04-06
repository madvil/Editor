#include "editortreewidgetmanager.h"

static EditorTreeWidgetManager *singletone;
//static QList<EditorTreeWidgetItem *> rootItems;

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

void EditorTreeWidgetManager::updateNames()
{
    if (lastSelected != 0 && lastSelected->getAssignedObject() != 0)
        lastSelected->getAssignedObject()->updateName();
}

void EditorTreeWidgetManager::addNewObject(BaseObject *object)
{
    qDebug() << "_1_ addNewObject" << object;
    EditorTreeWidgetItem *parentItem = 0;
    qDebug() << "_2_";
    bool resultOk = false;
    qDebug() << "_3_";
//    for (int i = 0; i < rootItems.count(); i++) {
//        qDebug() << "_4_" << QString::number(i) << 1;
//        parentItem = rootItems.at(i);

//        qDebug() << "_4_" << QString::number(i) << 2;
//        if (parentItem->isRoot() && parentItem->getName().compare(object->getRootName()) == 0) {
//            resultOk = true;
//            qDebug() << "_4_" << QString::number(i) << 3;
//            break;
//        }
//        qDebug() << "_4_" << QString::number(i) << 4;
//    }

    if (!resultOk) {
        qDebug() << "!resultOk 1";
        parentItem = new EditorTreeWidgetItem(parent);
        qDebug() << "!resultOk 2";
        parentItem->setName(object->getRootName());
        qDebug() << "!resultOk 3";
        parentItem->setIsRoot(true);
        qDebug() << "!resultOk 4";
//        rootItems << parentItem;
        qDebug() << "!resultOk 5";
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
