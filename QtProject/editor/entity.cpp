#include "entity.h"
#include "constants.h"

Entity::Entity(QtAbstractPropertyBrowser *propertyBrowser)
    : BaseObject(propertyBrowser)
{
    setRootName(ENTITY_NAME);
}

Entity::~Entity()
{

}
