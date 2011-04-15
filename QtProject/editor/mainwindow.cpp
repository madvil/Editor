#include <QSplitter>
#include <QHBoxLayout>
#include <QFileDialog>
#include <QFileInfo>
#include <QTextStream>
#include "mainwindow.h"
#include "entity.h"
#include "editortreewidgetmanager.h"
#include "texturesmanager.h"
#include "ui_mainwindow.h"

static MainWindow *singletone;

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    singletone = this;
//    setWindowState(Qt::WindowMaximized);
    setWindowTitle("2D Level Editor");
    glWidget = 0;

    //init part
    initTexturesListWidget();
    initPropertyBrowser();

    EditorTreeWidgetManager(ui->editorTreeWidget, propertyBrowser);
    scene = new Scene(propertyBrowser);

    initWidgets();
    initLayouts();
    initEditorToolBar();

    loadTexturesList();

    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()), this, SLOT(animate()));
}

MainWindow::~MainWindow()
{
    propertyBrowser->clear();
    glWidget = 0;
    delete ui;
    delete propertyManagers;
}

MainWindow *MainWindow::getInstance()
{
    return singletone;
}

void MainWindow::startUpdating()
{
    timer->start(5);
}

void MainWindow::addEntityToScene(QString path)
{
    scene->addEntity(TexturesManager::getInstance()->getTexture(path));
    glWidget->repaint();
}

bool MainWindow::eventFilter(QObject *target, QEvent *event)
{
    return false;
}

void MainWindow::initPropertyBrowser()
{
    propertyBrowser = new QtTreePropertyBrowser(this);
    propertyBrowser->setStyleSheet("border: 0px;");
    propertyBrowser->setIndentation(12);
    propertyManagers = new PropertyManagers(propertyBrowser);
    ui->generalTabVerticalLayout->addWidget(propertyBrowser);

    for (int i = 0; i < propertyManagers->count(); i++) {
        connect(propertyManagers->getSomePropertyManager(i), SIGNAL(propertyChanged(QtProperty*)),
                        this, SLOT(propertyChanged(QtProperty*)));
    }
}

void MainWindow::initWidgets()
{
    ui->editorTreeWidget->setIndentation(15);

    glWidget = new GLWidget(this, scene);
    ui->glViewVerticalLayout->addWidget(glWidget);
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

    QHBoxLayout *centralLayout = new QHBoxLayout;
    centralLayout->setMargin(2);
    ui->centralWidget->setLayout(centralLayout);
    ui->centralWidget->setFocus();
    centralLayout->addWidget(splitter2);
}

void MainWindow::initTexturesListWidget()
{
    TexturesManager(ui->textureListWidget);
    connect(addTextureItem(0)->getAddButton(), SIGNAL(clicked()), this, SLOT(addNewTexture()));
}

void MainWindow::initEditorToolBar()
{
    editorToolBar = new QToolBar;

    editorToolBar->addWidget(ui->addEntityToolBtn);
    ui->editorToolBarHorizontalLayout->addWidget(editorToolBar);
}

void MainWindow::saveTexturesList()
{
    QDir().mkdir("textures");
    QFile file("textures/list.txt");
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream ts(&file);
        ts.setCodec("UTF-8");

        for (int i = 0; i < TexturesManager::getInstance()->count(); i++) {
            ts << TexturesManager::getInstance()->getPath(i) << endl;
        }

        file.close();
    }
}

void MainWindow::loadTexturesList()
{
    QFile file("textures/list.txt");
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream ts(&file);
        ts.setCodec("UTF-8");

        QString line = ts.readLine();
        while (!line.isEmpty()) {
            addTextureItem(line);
            line = ts.readLine();
        }

        file.close();
    }
}

TextureListItemWidget *MainWindow::addTextureItem(int page)
{
    if (page == 1) {
        QDir().mkdir("textures");
        QString fname = QFileDialog::getOpenFileName(this, tr("Picture"), ".", tr("PNG (*.png)"));
        if (fname.isEmpty())
            return 0;

        TextureListItemWidget *textureItem = addTextureItem(fname);
        saveTexturesList();
        return textureItem;
    }

    QListWidgetItem *item = new QListWidgetItem(ui->textureListWidget);
    TextureListItemWidget *textureItem = new TextureListItemWidget;
    textureItem->setPage(0);
    item->setSizeHint(QSize(100, 100));

    ui->textureListWidget->setItemWidget(item, textureItem);

    return textureItem;
}

TextureListItemWidget *MainWindow::addTextureItem(QString path)
{
    QFileInfo file(path);

    if (!file.exists())
        return 0;

    QString name = file.baseName();
    QString fname = file.canonicalFilePath();
    TexturesManager::getInstance()->addTexture(fname);

    QListWidgetItem *item = new QListWidgetItem(ui->textureListWidget);
    TextureListItemWidget *textureItem = new TextureListItemWidget;
    textureItem->setPage(1);
    textureItem->setName(name);
    textureItem->setFilePath(fname);
    textureItem->setToolTip(name);
    item->setSizeHint(QSize(100, 100));

    ui->textureListWidget->setItemWidget(item, textureItem);
    return textureItem;
}

void MainWindow::addNewTexture()
{
    addTextureItem(1);
}

void MainWindow::animate()
{
    if (scene->animate())
        timer->stop();

    glWidget->repaint();
}

void MainWindow::on_actionExit_triggered()
{
    QApplication::exit();
}

void MainWindow::on_editorTreeWidget_itemClicked(QTreeWidgetItem *item, int column)
{
    EditorTreeWidgetItem *selectedItem = (EditorTreeWidgetItem *)item;
    if (!selectedItem->isRoot() && EditorTreeWidgetManager::getInstance() != 0) {
        propertyBrowser->clear();
        EditorTreeWidgetManager::getInstance()->select(selectedItem);
        glWidget->repaint();
    }
}

void MainWindow::propertyChanged(QtProperty *property)
{
    if (glWidget != 0)
        glWidget->repaint();

    EditorTreeWidgetManager::getInstance()->updateNames();
}

void MainWindow::on_pushButton_clicked()
{
    propertyBrowser->clear();
}

void MainWindow::on_addEntityToolBtn_clicked()
{
    scene->addEntity(TexturesManager::getInstance()->getNone())->select();
    glWidget->repaint();
}
