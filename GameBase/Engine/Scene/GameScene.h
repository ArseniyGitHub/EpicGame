//
// Created by Arsen on 23.11.2025.
//

#ifndef MY_APPLICATION_GAMESCENE_H
#define MY_APPLICATION_GAMESCENE_H
#include "Scene.h"
#include <raylib.h>
#include <vector>
#include "../Navigation/NavigationGrid.h"

class GameScene : PRIVATE Scene {
PUBLIC:
    Camera3D camera;
    NavigationGrid* grid;
    std::vector<Vector3> currPath;
    float
        camSpd = 20.f,
        zoomSpd = 30.f,
        cameraDistance = 15.f,
        camAngle = 45,
        camPich = 45,
        rotationSpd = 90;
    Vector2 hoveredCell{ -1, -1 };
    Vector3 startPos{ 0, 0, 0 }, endPos{ 0, 0, 0 };
PRIVATE:
    void initCamera();
    void draw(Game*);
    void update(Game*, float);
    void onEnter();
    void onExit();
    virtual ~GameScene();
    GameScene();
};

#endif //MY_APPLICATION_GAMESCENE_H
