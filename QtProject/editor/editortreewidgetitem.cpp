#include "constants.h"
#include "editortreewidgetitem.h"

void EditorTreeWidgetItem::init()
{
    setName(DEFAULT_NAME);
    setIsRoot(false);
    assignedObject = 0;
}

QString EditorTreeWidgetItem::getName()
{
    return name;
}

void EditorTreeWidgetItem::setName(QString name)
{
    this->name = name;
    setText(0, name);
}
