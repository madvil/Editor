#include "atlascreatorwidget.h"
#include <QDir>
#include <QtOpenGL>
#include "ui_atlascreatorwidget.h"
#include "entity.h"

class SimpleAtlas
{

};

AtlasCreatorWidget::AtlasCreatorWidget(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AtlasCreatorWidget)
{
    ui->setupUi(this);
    load();
}

AtlasCreatorWidget::~AtlasCreatorWidget()
{
    delete ui;
}

void AtlasCreatorWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);
    painter.beginNativePainting();
//    painter.fillRect(event->rect(), QBrush(QColor(0, 255, 0)));

    glClearColor(0.0, 0.0, 1.0, 1.0);

    painter.endNativePainting();
    painter.end();
}

void AtlasCreatorWidget::load()
{

    QFile file("atlases/list.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {

    }
}

void AtlasCreatorWidget::save()
{
    QDir().mkdir("atlases");
    QFile file("atlases/list.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {

    }

//    QDir("atlases").entryList("*.ent");
}
