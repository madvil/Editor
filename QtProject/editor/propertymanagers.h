#ifndef PROPERTYMANAGERS_H
#define PROPERTYMANAGERS_H

#include "qtpropertybrowser/qtpropertymanager.h"

class PropertyManagers
{
public:
    PropertyManagers(QtAbstractPropertyBrowser *parent);

    static PropertyManagers *getInstance();

    QtBoolPropertyManager *getBoolPropertyManager()             const { return boolManager;         }
    QtIntPropertyManager *getIntPropertyManager()               const { return intManager;          }
    QtDoublePropertyManager *getDoublePropertyManager()         const { return doubleManager;       }
    QtStringPropertyManager *getStringPropertyManager()         const { return stringManager;       }
    QtSizePropertyManager *getSizePropertyManager()             const { return sizeManager;         }
    QtRectPropertyManager *getRectPropertyManager()             const { return rectManager;         }
    QtSizePolicyPropertyManager *getSizePolicyPropertyManager() const { return sizePolicyManager;   }
    QtEnumPropertyManager *getEnumPropertyManager()             const { return enumManager;         }
    QtGroupPropertyManager *getGroupPropertyManager()           const { return groupManager;        }

protected:
    QtAbstractPropertyBrowser *parent;

    QtBoolPropertyManager *boolManager;
    QtIntPropertyManager *intManager;
    QtDoublePropertyManager *doubleManager;
    QtStringPropertyManager *stringManager;
    QtSizePropertyManager *sizeManager;
    QtRectPropertyManager *rectManager;
    QtSizePolicyPropertyManager *sizePolicyManager;
    QtEnumPropertyManager *enumManager;
    QtGroupPropertyManager *groupManager;
};

#endif // PROPERTYMANAGERS_H
