#include <QtGui>
#include "glwidget.h"
#include "mainwindow.h"

GLWidget::GLWidget(QWidget *parent, Scene *scene) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setAutoFillBackground(false);
    this->scene = scene;
    toSliding = false;
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    scene->paint(&painter, event);

    painter.end();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastX = event->x();
    lastXDelta = 0;

    if (event->button() == Qt::RightButton) {
        toSliding = true;
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    if (toSliding) {
        scene->slide(lastXDelta = lastX - event->x());
        lastX = event->x();
    }

    repaint();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (lastXDelta > 10 || lastXDelta < -10) {
        scene->animationSlide(lastXDelta);
        MainWindow::getInstance()->startUpdating();
    }

    toSliding = false;
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    if (event->orientation() == Qt::Horizontal) {
        scene->slide(event->delta());
        repaint();
    }
}
