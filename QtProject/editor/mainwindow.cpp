#include <QSplitter>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "entity.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("2D Level Editor");

    propertyBrowser = new QtTreePropertyBrowser();
    propertyBrowser->setStyleSheet("border: 0px;");
    propertyManagers = new PropertyManagers(propertyBrowser);
    ui->generalTabVerticalLayout->addWidget(propertyBrowser);

    QSplitter *splitter1 = new QSplitter(Qt::Vertical);
    splitter1->addWidget(ui->editorViewWidget);
    splitter1->addWidget(ui->bottomPanelWidget);
    splitter1->setCollapsible(0, false);
    splitter1->setCollapsible(1, false);
    splitter1->setStretchFactor(0, 1);
    splitter1->setStretchFactor(1, 0);

    QSplitter *splitter2 = new QSplitter(Qt::Horizontal);
    splitter2->addWidget(ui->tabWidget);
    splitter2->addWidget(splitter1);
    splitter2->setCollapsible(0, false);
    splitter2->setCollapsible(1, false);
    splitter2->setStretchFactor(0, 0);
    splitter2->setStretchFactor(1, 1);

    QHBoxLayout *centralLayout = new QHBoxLayout();
    centralLayout->setMargin(2);
    ui->centralWidget->setLayout(centralLayout);
    centralLayout->addWidget(splitter2);

    ui->centralWidget->setFocus();

    Entity *e = new Entity(propertyBrowser);
    e->setSelected(true);
}

MainWindow::~MainWindow()
{
    delete ui;
    delete propertyBrowser;
}
