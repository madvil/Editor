#include "entity.h"
#include "constants.h"
#include "propertymanagers.h"

Entity::Entity(QtAbstractPropertyBrowser *propertyBrowser)
    : BaseObject(propertyBrowser)
{
    setRootName(ENTITY_NAME);
    init();

    for (int i = 1; i < 11; i++)
    {
        addNewProperty("Entity " + QString::number(i), PropertyManagers::getInstance()->getStringPropertyManager());
    }
}
