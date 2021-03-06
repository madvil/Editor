#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include "qtpropertybrowser/qttreepropertybrowser.h"
#include "propertymanagers.h"
#include "texturelistitemwidget.h"
#include "atlascreatorwidget.h"
#include "glwidget.h"

namespace Ui {
    class MainWindow;
}

class QTimer;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    static MainWindow *getInstance();

    void startUpdating();
    void addEntityToScene(QString path);

protected:
    Ui::MainWindow *ui;
    QtTreePropertyBrowser *propertyBrowser;
    PropertyManagers *propertyManagers;
    GLWidget *glWidget;
    AtlasCreatorWidget *atlasCreatorWidget;
    Scene *scene;
    QTimer *timer;
    QString path;

    //editor toolbar
    QToolBar *editorToolBar;

    bool eventFilter(QObject *target, QEvent *event);
    void initPropertyBrowser();
    void initWidgets();
    void initLayouts();
    void initTexturesListWidget();

    void saveTexturesList();
    void loadTexturesList();

    TextureListItemWidget *addTextureItem(int page = 1);
    TextureListItemWidget *addTextureItem(QString path);

    void save(QString path, bool toExport);
    void load(QString path);

public slots:
    void addNewTexture();
    void animate();
    void on_actionExit_triggered();
    void on_editorTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void propertyChanged(QtProperty *property);

private slots:
    void on_actionExport_triggered();
    void on_actionLoad_triggered();
    void on_actionSave_as_new_triggered();
    void on_actionSave_triggered();
    void on_actionSet_landscape_texture_triggered();
    void on_actionSet_background_texture_triggered();
};

#endif // MAINWINDOW_H
