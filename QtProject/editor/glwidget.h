#ifndef GLWIDGET_H
#define GLWIDGET_H

#include <QGLWidget>
#include <QPainter>
#include <QPaintEvent>
#include <QMouseEvent>
#include <QWheelEvent>
#include "scene.h"

class GLWidget : public QGLWidget
{
    Q_OBJECT

public:
    GLWidget(QWidget *parent, Scene *scene);

    void setScene(Scene *scene) { this->scene = scene; }

protected:
    Scene *scene;
    int lastX;
    int lastY;
    int lastXDelta;
    int lastYDelta;
    bool toSliding;
    bool toTranslate;
    bool toTransform;

    void paintEvent(QPaintEvent *event);
    void mousePressEvent(QMouseEvent *event);
    void mouseMoveEvent(QMouseEvent *event);
    void mouseReleaseEvent(QMouseEvent *event);
    void wheelEvent(QWheelEvent* event);

private:

};
#endif // GLWIDGET_H
