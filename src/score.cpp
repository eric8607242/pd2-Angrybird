/*#include "score.h"

score::score()
{
    b2BodyDef bodydef;
    bodydef.type = b2_dynamicBody;
    bodydef.bullet = true;//讓body之間不會互相穿透
    bodydef.position.Set(x,y);
    bodydef.userData = this;//使用bird這個.cpp來存這個body的身體數據
    g_body = world->CreateBody(&bodydef);

    sc = 0;
    check = 40;
    setPlainText(QString("Score :"+QString::number(sc)));
    setFont(QFont("Arial",14));
}
void score::prscor()
{
    sc= sc+10;
    check--;
    setPlainText(QString("Score :"+QString::number(sc)));
    setFont(QFont("Arial",14));
}
/*void score::result()
{
     setPlainText(QString("Score :"+QString::number(sc)));
     setFont(QFont("Arial",28));
}*/
