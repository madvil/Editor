#include <QDebug>
#include "texturelistitemwidget.h"
#include "ui_texturelistitemwidget.h"
#include "mainwindow.h"

TextureListItemWidget::TextureListItemWidget(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::TextureListItemWidget)
{
    ui->setupUi(this);
}

TextureListItemWidget::~TextureListItemWidget()
{
    delete ui;
}

void TextureListItemWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (ui->stackedWidget->currentIndex() == 1) {
        MainWindow::getInstance()->addEntityToScene(fname);
    }
}

void TextureListItemWidget::setPage(int page)
{
    ui->stackedWidget->setCurrentIndex(page);
}

void TextureListItemWidget::setName(QString name)
{
    if (name.length() > 13) {
        ui->textureNameLabel->setText(name.left(13) + "...");
    } else {
        ui->textureNameLabel->setText(name);
    }
}

QPushButton *TextureListItemWidget::getAddButton()
{
    return ui->addPushButton;
}
