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

private:
    Ui::MainWindow *ui;
    QtTreePropertyBrowser *propertyBrowser;
    PropertyManagers *propertyManagers;
    GLWidget *glWidget;
    Scene *scene;
    QTimer *timer;

    void initWidgets();
    void initLayouts();
    void initTexturesListWidget();
    TextureListItemWidget *addTextureItem(int page = 1);

protected:
    bool eventFilter(QObject *target, QEvent *event);

public slots:
    void addNewTexture();
    void animate();

private slots:
    void on_actionExit_triggered();
    void on_pB_clicked();
};

#endif // MAINWINDOW_H
