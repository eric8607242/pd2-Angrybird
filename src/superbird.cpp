#include "superbird.h"

superbird::superbird(float x, float y, float radius, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,float density):GameItem(world)
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

void superbird::setLinearVelocity(b2Vec2 velocity)
{
    g_body->SetLinearVelocity(velocity);
}

void superbird::supergo()
{
    g_pixmap.setPixmap(QPixmap(":/image/iron.png").scaled(960/32*2,540/18*2));
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);
    b2CircleShape bodyshape;
    bodyshape.m_radius = 1;

    b2FixtureDef fixturedef;//b2fixturedeg 設定物理係數用
    fixturedef.shape = &bodyshape;
    fixturedef.density = 500;//設地各種重力,摩擦力等等的係數
    fixturedef.friction = BIRD_FRICTION;
    fixturedef.restitution = BIRD_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);
}
bool superbird::disapp()
{
    b2Vec2 ve;
    ve = g_body->GetLinearVelocity();
    int x = ve.x;
    int y = ve.y;
    if(x == 0 && y == 0)
    {
        return true;
    }
    return false;
}
