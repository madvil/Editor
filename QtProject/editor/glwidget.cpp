#include <QtGui>
#include "glwidget.h"
#include "mainwindow.h"
#include "editortreewidgetmanager.h"

Entity *lastEntity = 0;

GLWidget::GLWidget(QWidget *parent, Scene *scene) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setAutoFillBackground(false);
    this->scene = scene;

    toSliding = toTranslate = toTransform = false;
    lastX = lastY = lastXDelta = lastYDelta = 0;
}

void GLWidget::paintEvent(QPaintEvent *event)
{
    QPainter painter;
    painter.begin(this);

    scene->paint(&painter, event, this);

    painter.end();
}

void GLWidget::mousePressEvent(QMouseEvent *event)
{
    lastX = event->x();
    lastY = event->y();
    lastXDelta = lastYDelta = 0;

    if (event->button() == Qt::RightButton) {
        toSliding = true;
        scene->animationSlide(0);
    } else if (event->button() == Qt::LeftButton) {
        if (lastEntity != 0 && lastEntity->checkCorner(event->x(), event->y(), scene)) {
            scene->startModifyEntity(lastEntity);
            toTransform = true;
            return;
        }

        lastEntity = 0;
        EditorTreeWidgetManager::getInstance()->deselect();
        Entity *e = scene->getEntity(event->x(), event->y());
        EditorTreeWidgetItem *etwi = EditorTreeWidgetManager::getInstance()->getSelected();
        if (etwi != 0 && e != 0) {
            lastEntity = e;
            e->select();
            scene->startModifyEntity(e);

            if (e->isCheckedCorner()) {
                toTransform = true;
            } else {
                toTranslate = true;
            }
        }

        repaint();
    }
}

void GLWidget::mouseMoveEvent(QMouseEvent *event)
{
    lastXDelta = lastX - event->x();
    lastYDelta = lastY - event->y();
    lastX = event->x();
    lastY = event->y();

    if (toSliding) {
        scene->slide(lastXDelta);
    } else if (toTransform) {
        scene->transformEntity(lastXDelta, lastYDelta);
    } else if (toTranslate) {
        scene->translateEntity(lastXDelta, lastYDelta);
    }

    repaint();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (toSliding && (lastXDelta > 10 || lastXDelta < -10)) {
        scene->animationSlide(lastXDelta);
        MainWindow::getInstance()->startUpdating();
    }

    scene->endModifyEntity();
    toSliding = toTranslate = toTransform = false;
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    if (event->orientation() == Qt::Horizontal) {
        scene->slide(event->delta());
        repaint();
    }
}
