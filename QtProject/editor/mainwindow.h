#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QToolBar>
#include <QToolButton>
#include "qtpropertybrowser/qttreepropertybrowser.h"
#include "propertymanagers.h"
#include "texturelistitemwidget.h"
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
    Scene *scene;
    QTimer *timer;

    //editor toolbar
    QToolBar *editorToolBar;

    bool eventFilter(QObject *target, QEvent *event);
    void initPropertyBrowser();
    void initWidgets();
    void initLayouts();
    void initTexturesListWidget();
    void initEditorToolBar();

    void saveTexturesList();
    void loadTexturesList();

    TextureListItemWidget *addTextureItem(int page = 1);
    TextureListItemWidget *addTextureItem(QString path);

public slots:
    void addNewTexture();
    void animate();
    void on_actionExit_triggered();
    void on_editorTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void propertyChanged(QtProperty *property);
    void on_addEntityToolBtn_clicked();
    void on_pushButton_clicked();
};

#endif // MAINWINDOW_H
