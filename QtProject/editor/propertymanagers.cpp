#include "propertymanagers.h"
#include "qtpropertybrowser/qteditorfactory.h"

static PropertyManagers *singletone = 0;

PropertyManagers::PropertyManagers(QtAbstractPropertyBrowser *parent) {
    singletone = this;
    this->parent = parent;

    boolManager = new QtBoolPropertyManager(this->parent);
    intManager = new QtIntPropertyManager(this->parent);
    doubleManager = new QtDoublePropertyManager(this->parent);
    stringManager = new QtStringPropertyManager(this->parent);
    sizeManager = new QtSizePropertyManager(this->parent);
    rectManager = new QtRectPropertyManager(this->parent);
    sizePolicyManager = new QtSizePolicyPropertyManager(this->parent);
    enumManager = new QtEnumPropertyManager(this->parent);
    groupManager = new QtGroupPropertyManager(this->parent);

    params << boolManager << intManager << doubleManager << stringManager <<
                sizeManager << rectManager << sizePolicyManager << enumManager << groupManager;

    QtCheckBoxFactory *checkBoxFactory = new QtCheckBoxFactory(this->parent);
    QtSpinBoxFactory *spinBoxFactory = new QtSpinBoxFactory(this->parent);
    QtDoubleSpinBoxFactory *doubleSpinBoxFactory = new QtDoubleSpinBoxFactory(this->parent);
    QtLineEditFactory *lineEditFactory = new QtLineEditFactory(this->parent);
    QtEnumEditorFactory *comboBoxFactory = new QtEnumEditorFactory(this->parent);

    this->parent->setFactoryForManager(boolManager, checkBoxFactory);
    this->parent->setFactoryForManager(intManager, spinBoxFactory);
    this->parent->setFactoryForManager(doubleManager, doubleSpinBoxFactory);
    this->parent->setFactoryForManager(stringManager, lineEditFactory);
    this->parent->setFactoryForManager(sizeManager->subIntPropertyManager(), spinBoxFactory);
    this->parent->setFactoryForManager(rectManager->subIntPropertyManager(), spinBoxFactory);
    this->parent->setFactoryForManager(sizePolicyManager->subIntPropertyManager(), spinBoxFactory);
    this->parent->setFactoryForManager(sizePolicyManager->subEnumPropertyManager(), comboBoxFactory);
    this->parent->setFactoryForManager(enumManager, comboBoxFactory);
}

PropertyManagers::~PropertyManagers() {
    delete boolManager;
    delete intManager;
    delete doubleManager;
    delete stringManager;
    delete sizeManager;
    delete rectManager;
    delete sizePolicyManager;
    delete enumManager;
    delete groupManager;
}

PropertyManagers *PropertyManagers::getInstance() {
    return singletone;
}
