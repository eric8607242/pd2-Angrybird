#include "scene.h"

Scene::Scene()
{

}
void Scene::settingBg(&maindow)
{
    QImage bg;
    bg.load(":/image/eb568585f2d196d49c5fed28f2606ae6.jpg");
    bg = bg.scaled(800,600); // you can also change here
    this->setBackgroundBrush(bg);
}
