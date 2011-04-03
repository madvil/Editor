#ifndef TEXTURELISTITEMWIDGET_H
#define TEXTURELISTITEMWIDGET_H

#include <QWidget>
#include <qpushbutton.h>

namespace Ui {
    class TextureListItemWidget;
}

class TextureListItemWidget : public QWidget
{
    Q_OBJECT

public:
    explicit TextureListItemWidget(QWidget *parent = 0);
    ~TextureListItemWidget();

    void setPage(int page);
    QPushButton *getAddButton();

protected:
    Ui::TextureListItemWidget *ui;

signals:
    void addClicked();
};

#endif // TEXTURELISTITEMWIDGET_H
