#ifndef ATLASCREATORWIDGET_H
#define ATLASCREATORWIDGET_H

#include <QWidget>
#include <QVector>

namespace Ui {
    class AtlasCreatorWidget;
}

class SimpleAtlas;

class AtlasCreatorWidget : public QWidget
{
    Q_OBJECT

public:
    explicit AtlasCreatorWidget(QWidget *parent = 0);
    ~AtlasCreatorWidget();

private:
    Ui::AtlasCreatorWidget *ui;

protected:
    QVector<SimpleAtlas *> atlases;

    void paintEvent(QPaintEvent *event);
    void load();
    void save();
};

#endif // ATLASCREATORWIDGET_H
