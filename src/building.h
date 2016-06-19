#ifndef BUILDING_H
#define BUILDING_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>


#define BUILDING_DENSITY 0.5f
#define BUILDING_FRICTION 1.0f
#define BUILDING_RESTITUTION 0.5f

class building : public GameItem
{
public:
    building(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,float density);
    int height;
};

#endif // BUILDING_H
