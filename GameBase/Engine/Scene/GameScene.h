//
// Created by Arsen on 23.11.2025.
//

#ifndef MY_APPLICATION_GAMESCENE_H
#define MY_APPLICATION_GAMESCENE_H
#include "Scene.h"
#include <raylib.h>

class GameScene : public Scene {
private:
    Camera3D camera;
public:
    void draw(Game*);
    void update(Game*, float);
    void onEnter();
    void onExit();
    ~GameScene();
    GameScene();
};

#endif //MY_APPLICATION_GAMESCENE_H
