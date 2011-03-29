#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "qtpropertybrowser/qttreepropertybrowser.h"
#include "propertymanagers.h"

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QtTreePropertyBrowser *propertyBrowser;
    PropertyManagers *propertyManagers;

};

#endif // MAINWINDOW_H
