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

//    new Entity(propertyBrowser);
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
    scene->addEntity(TexturesManager::getInstance()->getTexture(path))->select();
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

void MainWindow::save(QString path, bool toExport)
{
    this->path = path;
    setWindowTitle("2D Level Editor [" + path + "]");

    QFile file(path);
    if (file.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QXmlStreamWriter xmlWriter(&file);
        xmlWriter.setAutoFormatting(true);
        xmlWriter.writeStartDocument();
        xmlWriter.writeStartElement("level");

        scene->save(&xmlWriter, toExport);

        xmlWriter.writeEndDocument();
        file.close();
    }
}

void MainWindow::load(QString path)
{
    this->path = path;
    setWindowTitle("2D Level Editor [" + path + "]");

    QFile file(path);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text)) {
        ui->editorTreeWidget->clear();
        EditorTreeWidgetManager::getInstance()->clear();

        delete scene;
        scene = new Scene(propertyBrowser);
        glWidget->setScene(scene);

        QXmlStreamReader xmlReader(&file);

        xmlReader.readNext();
        while (!xmlReader.atEnd())
        {
            if (xmlReader.isStartElement()) {
                if (xmlReader.name() == "level") {
                    scene->load(&xmlReader);
                }
            } else {
                xmlReader.readNext();
            }
        }

        file.close();
    }

    glWidget->repaint();
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

}

void MainWindow::on_addEntityToolBtn_clicked()
{
    addEntityToScene("");
}

void MainWindow::on_actionSave_triggered()
{
    if (path.isEmpty()) {
        on_actionSave_as_new_triggered();
    } else {
        save(path, false);
    }
}

void MainWindow::on_actionSave_as_new_triggered()
{
    save(QFileDialog::getSaveFileName(this, tr("Level"), ".", tr("XML (*.xml)")), false);
}

void MainWindow::on_actionLoad_triggered()
{
    load(QFileDialog::getOpenFileName(this, tr("Level"), ".", tr("XML (*.xml)")));
}

void MainWindow::on_editorTreeWidget_doubleClicked(QModelIndex index)
{

}

void MainWindow::on_actionExport_triggered()
{
    save(QFileDialog::getSaveFileName(this, tr("Level"), ".", tr("XML (*.xml)")), true);
}
