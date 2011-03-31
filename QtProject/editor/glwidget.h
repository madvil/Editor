#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include "scene.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent, Scene *scene);

protected:
    Scene *scene;
    int lastX;
    int lastXDelta;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);

private:

};
#endif // GLWIDGET_H
