//
// Created by Arsen on 23.11.2025.
//

#include "GameScene.h"
#include "../Game.h"
#include "../Entity/Player.h"



void GameScene::draw(Game *game) {
    ClearBackground(Color{0, 100, 100, 50});
    DrawText(TextFormat("Windows 95 is starting... fps: %d", GetFPS()), 50, 50, 90, Color{0, 255, 0, 100});
    BeginMode3D(camera);
    std::vector<Vector3> cps = {
            {0, 0, 0},
            {10, 0, 0},
            {0, 0, 10}
    };
    for(auto& e : cps){
        DrawCube(e, 2, 2, 2, Color({255, 255, 255, 254}));
        DrawCubeWires(e, 2, 2, 2, Color({0, 0, 0, 254}));
    }

    EndMode3D();
}

void GameScene::update(Game *game, float) {
    camera.target = {0, 0, 0};
    camera.position = game->getPlayer().getPos();
}

void GameScene::onEnter() {
    camera.fovy = 45;
    camera.projection = CAMERA_FIRST_PERSON;
    camera.up = Vector3{0, 1, 0};
}

void GameScene::onExit() {

}

GameScene::~GameScene() {
    this->onExit();
}

GameScene::GameScene() {
    this->onEnter();
}
