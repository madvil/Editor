#include <qtimer.h>
#include <QDebug>
#include "scene.h"
#include "mainwindow.h"

Scene::Scene(QWidget *parent) : QObject(parent)
{
    drawDebugInfo = true;
    sliding = 0;
    animSliding = 0;

    background = QBrush(QColor(100, 130, 200));
    transparentBlack = QBrush(QColor(0, 0, 0, 80));
    debugPen = QPen(Qt::white);
    debugPen.setWidth(1);
}

void Scene::paint(QPainter *painter, QPaintEvent *event)
{
    int deltaHeight = (event->rect().height() / 6);
    painter->fillRect(event->rect(), background);
    painter->translate(-sliding, 0);

    //debug draws
    painter->resetMatrix();
    painter->setPen(debugPen);

    painter->fillRect(QRect(0, 0, event->rect().width(), deltaHeight), transparentBlack);
    painter->fillRect(QRect(0, deltaHeight * 5, event->rect().width(), deltaHeight * 6), transparentBlack);

    painter->drawLine(QPoint(0, deltaHeight), QPoint(event->rect().width(), deltaHeight));
    painter->drawLine(QPoint(0, deltaHeight * 5), QPoint(event->rect().width(), deltaHeight * 5));

    painter->translate(-sliding, 0);

    int start = sliding / 100;
    int count = start + event->rect().width() / 100 + 2;
    for (int i = start; i < count; i++)
    {
        painter->drawText(i * 100 + 4, deltaHeight * 5 + 15, QString::number(i));
        painter->drawText(i * 100 + 4, deltaHeight - 6, QString::number(i));
        painter->drawLine(QPoint(i * 100, deltaHeight), QPoint(i * 100, deltaHeight - 5));
        painter->drawLine(QPoint(i * 100, deltaHeight * 5), QPoint(i * 100, deltaHeight * 5 + 5));
    }

    if (drawDebugInfo)
    {

    }
}

bool Scene::animate()
{
    if (animSliding != 0)
    {
        animSliding = (int)((float)animSliding * (0.95));
        slide(animSliding);

        if ((animSliding > 0 && animSliding < 0.001) || (animSliding < 0 && animSliding > -0.001))
        {
            animSliding = 0;
        }
    } else {
        return true;
    }

    return false;
}
