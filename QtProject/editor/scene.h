#ifndef SCENE_H
#define SCENE_H

#include <QBrush>
#include <QFont>
#include <QPen>
#include <QPainter>
#include <QPaintEvent>

class Scene : public QObject
{
    Q_OBJECT
public:
    explicit Scene(QWidget *parent = 0);
    void paint(QPainter *painter, QPaintEvent *event);
    bool animate(); //true whet animate ended

    void setDrawDebugInfo(bool val) { drawDebugInfo = val; }
    void slide(int slideDelta) { sliding += slideDelta; if (sliding < 0) sliding = 0; }
    int getSlide() { return sliding; }
    void animationSlide(int animSliding) { this->animSliding = animSliding; }

protected:
    QBrush background;
    QBrush transparentBlack;
    QPen debugPen;
    bool drawDebugInfo;
    int sliding;
    int animSliding;

signals:

};

#endif // SCENE_H
