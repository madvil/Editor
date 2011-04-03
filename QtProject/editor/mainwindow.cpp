#include <QSplitter>
#include <QHBoxLayout>
#include "mainwindow.h"
#include "entity.h"
#include "editortreewidgetmanager.h"
#include "ui_mainwindow.h"

static MainWindow *singletone;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    singletone = this;
    setWindowState(Qt::WindowMaximized);
    setWindowTitle("2D Level Editor");

    scene = new Scene(this);
    EditorTreeWidgetManager(ui->editorTreeWidget);

    //init part
    initWidgets();
    initLayouts();
    initTexturesListWidget();

    Entity *e = new Entity(propertyBrowser);
    e->setName("name 1");

    e = new Entity(propertyBrowser);
    e->setName("name 2");

    e = new Entity(propertyBrowser);
    e->setName("name 3");

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
}

MainWindow::~MainWindow()
{
    delete ui;
    delete propertyBrowser;
}

MainWindow *MainWindow::getInstance()
{
    return singletone;
}

void MainWindow::startUpdating()
{
    timer->start(5);
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    return false;
}

void MainWindow::initWidgets()
{
    ui->editorTreeWidget->setIndentation(15);

    glWidget = new GLWidget(this, scene);
    ui->glViewVerticalLayout->addWidget(glWidget);

    propertyBrowser = new QtTreePropertyBrowser();
    propertyBrowser->setStyleSheet("border: 0px;");
    propertyBrowser->setIndentation(12);
    propertyManagers = new PropertyManagers(propertyBrowser);
    ui->generalTabVerticalLayout->addWidget(propertyBrowser);
}

void MainWindow::initLayouts()
{
    QSplitter *splitter1 = new QSplitter(Qt::Vertical);
    splitter1->addWidget(ui->editorTabWidget);
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
    ui->centralWidget->setFocus();
    centralLayout->addWidget(splitter2);
}

void MainWindow::initTexturesListWidget()
{
    connect(addTextureItem(0)->getAddButton(), SIGNAL(clicked()), this, SLOT(addNewTexture()));
}

TextureListItemWidget *MainWindow::addTextureItem(int page)
{
    QListWidgetItem *item = new QListWidgetItem(ui->textureListWidget);
    TextureListItemWidget *textureItem = new TextureListItemWidget();
    textureItem->setPage(page);
    item->setSizeHint(QSize(100, 100));

    ui->textureListWidget->setItemWidget(item, textureItem);
    return textureItem;
}

void MainWindow::addNewTexture()
{
    addTextureItem();
}

void MainWindow::animate()
{
    if (scene->animate())
    {
        timer->stop();
    }

    glWidget->repaint();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_editorTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    EditorTreeWidgetItem *selectedItem = (EditorTreeWidgetItem *)item;
    if (!selectedItem->isRoot() && EditorTreeWidgetManager::getInstance() != 0)
    {
        EditorTreeWidgetManager::getInstance()->select(selectedItem);
    }
}
