#include "texturelistitemwidget.h"
#include "ui_texturelistitemwidget.h"

TextureListItemWidget::TextureListItemWidget(QWidget *parent) : QWidget(parent),
                                                    ui(new Ui::TextureListItemWidget) {
    ui->setupUi(this);
}

TextureListItemWidget::~TextureListItemWidget() {
    delete ui;
}

void TextureListItemWidget::setPage(int page) {
    ui->stackedWidget->setCurrentIndex(page);
}

QPushButton *TextureListItemWidget::getAddButton() {
    return ui->addPushButton;
}
