#include "gameitem.h"

#include <iostream>

GameItem::GameItem(b2World *world)://用意再將其他的BOX2D的OBJECT可以透過gameitem轉換座標值等等的東西
    g_body(NULL),g_world(world)
{
}

GameItem::~GameItem()
{
    g_world->DestroyBody(g_body);
}

QSizeF GameItem::g_windowsize = QSizeF();
QSizeF GameItem::g_worldsize = QSizeF();

void GameItem::setGlobalSize(QSizeF worldsize, QSizeF windowsize)
{
    g_worldsize = worldsize;
    g_windowsize = windowsize;
}

void GameItem::paint()
{
    b2Vec2 pos = g_body->GetPosition();//v2Vec2是存放位置的vector
    //std::cout << g_body->GetAngle() << std::endl;
    QPointF mappedPoint;//用浮點數去計算位置精準度
    mappedPoint.setX(((pos.x-g_size.width()/2) * g_windowsize.width())/g_worldsize.width());//從box2D把座標直轉成QT的座標
    mappedPoint.setY((1.0f - (pos.y+g_size.height()/2)/g_worldsize.height()) * g_windowsize.height());
    g_pixmap.setPos(mappedPoint);
    g_pixmap.resetTransform();
    g_pixmap.setRotation(-(g_body->GetAngle()*180/3.14159));
}

void GameItem::supergo()
{

}
