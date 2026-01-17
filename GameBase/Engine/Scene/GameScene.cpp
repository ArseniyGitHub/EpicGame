//
// Created by Arsen on 23.11.2025.
//

#include "GameScene.h"
#include "../Game.h"
#include "../Entity/Player.h"
#include <iostream>



void GameScene::draw(Game *game) {
    ClearBackground(Color{0, 0, 0, 255});
    BeginMode3D(camera);
    
    for (size_t y = 0; y < grid->height; y++) {
        for (size_t x = 0; x < grid->width; x++) {
            Node* n = grid->getNode(x, y);
            Vector3 pos = { x * grid->cellSize, 0, y * grid->cellSize };
            if (not n->walkable) {
                DrawCube(pos, grid->cellSize * 0.7, 0.5, grid->cellSize * 0.7, MAROON);
                DrawCubeWires(pos, grid->cellSize * 0.7, 0.5, grid->cellSize * 0.7, RED);
            }
            else {
                DrawCubeWires(pos, grid->cellSize, 0, grid->cellSize, DARKGRAY);
            }
            if (hoveredCell.x == x && hoveredCell.y == y) {
                DrawCube({ pos.x, 0.1f, pos.z }, grid->cellSize, 0.1, grid->cellSize, { 255, 255, 255, 100 });
            }
        }
    }
    DrawSphere(Vector3Add(startPos, { 0.f, 0.5f, 0.f }), 0.4, GREEN);
    DrawSphere(Vector3Add(endPos, { 0.f, 0.5f, 0.f }), 0.4, BLUE);
    if (currPath.size() > 1) {
        for (size_t i = 0; i < currPath.size() - 1; i++) {
            Vector3
                p1 = Vector3Add(currPath[i], { 0.f, 0.2f, 0.f }),
                p2 = Vector3Add(currPath[i + 1], { 0.f, 0.2f, 0.f });
            DrawLine3D(p1, p2, YELLOW);
            DrawSphere(p1, 0.15f, ORANGE);
        }
    }

    EndMode3D();
}

void GameScene::initCamera() {
    camera.fovy = 45;
    camera.projection = CAMERA_PERSPECTIVE;
    camera.up = Vector3{ 0, 1, 0 };
    camera.position = { 15, 15, 15 };
    camera.target = { 10, 0, 10 };
    camAngle = 45;
    camPich = 45;
    cameraDistance = 15;
}

void GameScene::update(Game *game, float dt) {
    Vector3 moveVec{ 0, 0, 0 };
    
    if (IsKeyDown(KEY_LEFT))
        camAngle += rotationSpd * dt;
    if (IsKeyDown(KEY_RIGHT))
        camAngle -= rotationSpd * dt;
    if (IsKeyDown(KEY_UP))
        camPich += rotationSpd * dt;
    if (IsKeyDown(KEY_DOWN))
        camPich -= rotationSpd * dt;
    if (IsKeyPressed(KEY_R))
        initCamera();

    float wheel = GetMouseWheelMove();
    cameraDistance -= wheel * 2;
    if (cameraDistance < 5)cameraDistance = 5;
    if (cameraDistance > 60)cameraDistance = 60;

    if (camPich > 85) camPich = 85;
    if (camPich < 10) camPich = 10;
    Vector3 forward = Vector3Normalize(Vector3Subtract(camera.target, camera.position));
    forward.y = 0;
    Vector3 right = { -forward.z, 0.f, forward.x };

    if (IsKeyDown(KEY_W))
        moveVec = Vector3Add(moveVec, forward);
    if (IsKeyDown(KEY_S))
        moveVec = Vector3Subtract(moveVec, forward);
    if (IsKeyDown(KEY_A))
        moveVec = Vector3Subtract(moveVec, right);
    if (IsKeyDown(KEY_D))
        moveVec = Vector3Add(moveVec, right);

    

    
    if (Vector3Length(moveVec) > 0) {
        moveVec = Vector3Normalize(moveVec);
        moveVec = Vector3Scale(moveVec, camSpd * dt);
        // camera.position = Vector3Add(camera.position, moveVec);
        camera.target = Vector3Add(camera.target, moveVec);
    }

    float hDist = cameraDistance * cosf(camPich * DEG2RAD);
    float vDist = cameraDistance * sinf(camPich * DEG2RAD);
    float offsetX = hDist * sinf(camAngle * DEG2RAD);
    float offsetZ = hDist * cosf(camAngle * DEG2RAD);

    camera.position.x = camera.target.x - offsetX;
    camera.position.z = camera.target.z - offsetZ;
    camera.position.y = camera.target.y + vDist;

    Ray ray = GetMouseRay(GetMousePosition(), camera);
    if (ray.direction.y != 0) {
        float distance = -ray.position.y / ray.direction.y;
        Vector3 worldPaint = Vector3Add(ray.position, Vector3Scale(ray.direction, distance)); // worldPoint
        int
            gx = round(worldPaint.x / grid->cellSize),
            gy = round(worldPaint.z / grid->cellSize);

        if (gx >= 0 && gx < grid->width && gy >= 0 && gy < grid->height) {
            hoveredCell = { (float)gx, (float)gy };
            if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                //std::cout << gx << "  " << gy << std::endl;
                Node* n = grid->getNode(gx, gy);
                if (n) n->walkable = !n->walkable;
                currPath = grid->findPath(startPos, endPos);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                endPos = { gx * grid->cellSize, 0.f, gy * grid->cellSize };
                currPath = grid->findPath(startPos, endPos);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
                startPos = { gx * grid->cellSize, 0.f, gy * grid->cellSize };
                currPath = grid->findPath(startPos, endPos);
            }
        }
        else {
            hoveredCell = { -1, -1 };
        }
    }
}

void GameScene::onEnter() {
    initCamera();
    grid = new NavigationGrid(15, 15, 1.5f);
}

void GameScene::onExit() {

}

GameScene::~GameScene() {
    this->onExit();
}

GameScene::GameScene() {
    this->onEnter();
}
