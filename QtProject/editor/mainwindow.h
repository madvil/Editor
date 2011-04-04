#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
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

protected:
    Ui::MainWindow *ui;
    QtTreePropertyBrowser *propertyBrowser;
    PropertyManagers *propertyManagers;
    GLWidget *glWidget;
    Scene *scene;
    QTimer *timer;

    bool eventFilter(QObject *target, QEvent *event);
    void initPropertyBrowser();
    void initWidgets();
    void initLayouts();
    void initTexturesListWidget();
    TextureListItemWidget *addTextureItem(int page = 1);

public slots:
    void addNewTexture();
    void animate();
    void on_actionExit_triggered();
    void on_editorTreeWidget_itemClicked(QTreeWidgetItem *item, int column);
    void propertyChanged(QtProperty *property);

};

#endif // MAINWINDOW_H
