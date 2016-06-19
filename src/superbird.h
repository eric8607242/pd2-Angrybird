#ifndef SUPERBIRD_H
#define SUPERBIRD_H

#include <gameitem.h>
#include <QPixmap>
#include <QGraphicsScene>
#include <QTimer>

#define BIRD_DENSITY 100.0f
#define BIRD_FRICTION 0.2f
#define BIRD_RESTITUTION 0.5f

class superbird : public GameItem
{
public:
    superbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,float density);
    void setLinearVelocity(b2Vec2 velocity);
    void supergo();
    bool disapp();
};

#endif // BIRD_H
