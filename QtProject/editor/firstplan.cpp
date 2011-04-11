#include "firstplan.h"
#include "constants.h"
#include "scene.h"

Firstplan::Firstplan(QtAbstractPropertyBrowser *propertyBrowser, Scene *scene) : BaseObject(propertyBrowser)
{
    setRootName(CORE_GROUP);
    setName(FIRSTPLAN_NAME);
    init();
}

void Firstplan::paint(QPainter *painter, QPaintEvent *event)
{

}
