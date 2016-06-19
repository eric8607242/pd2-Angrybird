#ifndef BG_H
#define BG_H

#include <gameitem.h>
#include <QGraphicsScene>


class bg : public GameItem
{
public:
    bg(float x, float y, float w, float h, QPixmap pixmap, b2World *world, QGraphicsScene *scene);
};

#endif // BG_H
