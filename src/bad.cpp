#include "bad.h"

bad::bad(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,float density):GameItem(world)
{
    // Set pixmap
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);//設中心點
    g_size = QSizeF(radius*2,radius*2);

    // Create Body
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;//讓body之間不會互相穿透
    bodydef.position.Set(x,y);
    bodydef.userData = this;//使用bird這個.cpp來存這個body的身體數據
    g_body = world->CreateBody(&bodydef);

    b2CircleShape bodyshape;
    bodyshape.m_radius = radius;

    b2FixtureDef fixturedef;//b2fixturedeg 設定物理係數用
    fixturedef.shape = &bodyshape;
    fixturedef.density = density;//設地各種重力,摩擦力等等的係數
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    // Bound timer
    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);
}

void bad::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

bool bad::getvelocity()
{
    b2Vec2 ve;
    ve = g_body->GetLinearVelocity();
    float x = ve.x;
    float y = ve.y;
    if(x != 0 || y != 0)
    {
        return true;
    }
    return false;
}
