//
// Created by Arsen on 23.11.2025.
//

#pragma once
#include "Scene.h"
#include <raylib.h>
#include <vector>
#include "../Navigation/NavigationGrid.h"
#include "../AI/PathNet.h"
#include "../Entity/Terminator.h"
#include <torch/torch.h>

/*
struct TrainingSample {
    torch::Tensor input;

};
*/


class GameScene : public Scene {
private:
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
    std::shared_ptr<Terminator> terminator;
    std::shared_ptr<PathNet> aiModel;
    void handleUserInput();
    void syncTerminator(float);
    void updateCamera(float);
public:
    void initCamera();
    void draw(Game*);
    void update(Game*, float);
    void onEnter();
    void onExit();
    virtual ~GameScene();
    GameScene();
};
