#include <QtGui>
#include "qgl.h"
#include "glwidget.h"
#include "mainwindow.h"
#include "editortreewidgetmanager.h"

Movable *lastMovable = 0;

GLWidget::GLWidget(QWidget *parent, Scene *scene) : QGLWidget(QGLFormat(QGL::SampleBuffers), parent)
{
    setAutoFillBackground(false);
    setScene(scene);

    toSliding = toTranslate = toTransform = false;
    lastX = lastY = lastXDelta = lastYDelta = 0;
}

SimpleTexture *GLWidget::loadTexture(QString path)
{
    SimpleTexture *st = new SimpleTexture;
    QPixmap pmap(path);

    st->path = path;
    st->id = bindTexture(pmap, GL_TEXTURE_2D);
    st->width = pmap.width();
    st->height = pmap.height();

    return st;
}

void GLWidget::initializeGL()
{

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
        if (QApplication::keyboardModifiers() == Qt::ControlModifier) {
            lastMovable = 0;
            EditorTreeWidgetManager::getInstance()->deselect();
            scene->getLandscape()->addMover(event->x(), event->y());
        } else {
            if (lastMovable != 0 && lastMovable->checkCorner(event->x(), event->y(), scene)) {
                scene->startModifyMovable(lastMovable);
                toTransform = true;
                return;
            }

            lastMovable = 0;
            EditorTreeWidgetManager::getInstance()->deselect();
            Movable *m = scene->getMovable(event->x(), event->y());
            EditorTreeWidgetItem *etwi = EditorTreeWidgetManager::getInstance()->getSelected();
            if (etwi != 0 && m != 0) {
                lastMovable = m;
                m->select();
                scene->startModifyMovable(m);

                if (m->isCheckedCorner()) {
                    toTransform = true;
                } else {
                    toTranslate = true;
                }
            }
        }

        repaint();
    }
}

void GLWidget::mouseDoubleClickEvent(QMouseEvent *event)
{
    if (lastMovable != 0) {

    }
    repaint();
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
        scene->transformMovable(lastXDelta, lastYDelta);
    } else if (toTranslate) {
        scene->translateMovable(lastXDelta, lastYDelta);
    }

    repaint();
}

void GLWidget::mouseReleaseEvent(QMouseEvent *event)
{
    if (toSliding && (lastXDelta > 10 || lastXDelta < -10)) {
        scene->animationSlide(lastXDelta);
        MainWindow::getInstance()->startUpdating();
    }

    scene->endModifyMovable();
    toSliding = toTranslate = toTransform = false;
}

void GLWidget::wheelEvent(QWheelEvent* event)
{
    if (event->orientation() == Qt::Horizontal) {
        scene->slide(event->delta());
        repaint();
    }
}
