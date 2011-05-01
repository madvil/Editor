#ifndef EDITORTREEWIDGETITEM_H
#define EDITORTREEWIDGETITEM_H

#include <QTreeWidgetItem>

class BaseObject;

class EditorTreeWidgetItem : public QTreeWidgetItem
{
public:
    EditorTreeWidgetItem() : QTreeWidgetItem(0) { init(); }

    EditorTreeWidgetItem(QTreeWidgetItem *parent) :
            QTreeWidgetItem(parent) { init(); }

    EditorTreeWidgetItem(QTreeWidget *parent) :
            QTreeWidgetItem(parent) { init(); }

    QString getName();
    void setName(QString name);

    bool isRoot() const { return root; }
    void setIsRoot(bool val) { root = val; }

    void assignObject(BaseObject *object) { assignedObject = object; }
    BaseObject *getAssignedObject() { return assignedObject; }

protected:
    QString name;
    BaseObject *assignedObject;
    bool root;

    void init();

};

#endif // EDITORTREEWIDGETITEM_H
