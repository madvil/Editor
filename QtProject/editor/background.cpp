#include "background.h"
#include "constants.h"
#include "propertymanagers.h"

Background::Background(QtAbstractPropertyBrowser *propertyBrowser)
    : BaseObject(propertyBrowser)
{
    setRootName(BACKGROUND_NAME);
    init();
}
