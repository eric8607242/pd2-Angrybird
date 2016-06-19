#ifndef SCENE_H
#define SCENE_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QImage>

class Scene : public QGraphicsScene
{
public:
    Scene();
    void settingBg();
};

#endif // SCENE_H
