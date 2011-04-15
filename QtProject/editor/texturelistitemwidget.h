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

    void mouseDoubleClickEvent(QMouseEvent *event);

    void setPage(int page);
    void setName(QString name);
    QPushButton *getAddButton();

    void setFilePath(QString fname) { this->fname = fname; }

protected:
    Ui::TextureListItemWidget *ui;
    QString fname;

signals:
    void addClicked();
};

#endif // TEXTURELISTITEMWIDGET_H
