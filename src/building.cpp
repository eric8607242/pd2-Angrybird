#include "building.h"

building::building(float x, float y, float w, float h, QTimer *timer, QPixmap pixmap, b2World *world, QGraphicsScene *scene,float density):GameItem(world)
{
    g_pixmap.setPixmap(pixmap);
    g_pixmap.setTransformOriginPoint(g_pixmap.boundingRect().width()/2,g_pixmap.boundingRect().height()/2);//設中心點
    g_size = QSizeF(w,h);


    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;//讓body之間不會互相穿透
    bodydef.position.Set(x,y);
    bodydef.userData = this;//使用bird這個.cpp來存這個body的身體數據
    g_body = world->CreateBody(&bodydef);

    b2PolygonShape bodyshape;
    bodyshape.SetAsBox(w/2,h/2);

    b2FixtureDef fixturedef;//b2fixturedeg 設定物理係數用
    fixturedef.shape = &bodyshape;
    fixturedef.density = density;//設地各種重力,摩擦力等等的係數
    fixturedef.friction = BUILDING_FRICTION;
    fixturedef.restitution = BUILDING_RESTITUTION;
    g_body->SetAngularDamping(3);
    g_body->CreateFixture(&fixturedef);

    connect(timer, SIGNAL(timeout()), this,SLOT(paint()));

    scene->addItem(&g_pixmap);

}
