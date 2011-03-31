#include "entity.h"
#include "constants.h"
#include "propertymanagers.h"

Entity::Entity(QtAbstractPropertyBrowser *propertyBrowser)
    : BaseObject(propertyBrowser)
{
    setRootName(ENTITY_NAME);

    for (int i = 1; i < 101; i++)
    {
        addNewProperty("Entity " + QString::number(i), PropertyManagers::getInstance()->getStringPropertyManager());
    }
}
