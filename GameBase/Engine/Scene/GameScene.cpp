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
    terminator->draw();

    EndMode3D();

    DrawRectangle(10, 10, 450, 150, Color{0, 0, 0, 128});
    DrawText(TextFormat("mode: %s", useAI ? "NN" : "A*"), 20, 20, 25, useAI ? SKYBLUE : LIME);
    DrawText(TextFormat("training: %s; data: %d", isTraining ? "true" : "false", dataset.size()), 20, 55, 25, isTraining ? RED : GRAY);
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
    if (IsKeyPressed(KEY_SPACE))
        useAI = !useAI;
    if (IsKeyPressed(KEY_T))
        isTraining = !isTraining;
    if (IsKeyPressed(KEY_P))
    {
        torch::save(aiModel, "PathNet.ai");
        std::cout << "Модель сохранена!\n";
    }

    if (isTraining) {
        if (!currPath.empty()) {
            collectDataFromAStar();
        }
        trainStep();
    }

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
                currPath = grid->findPath(terminator->pos, endPos);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
                endPos = { gx * grid->cellSize, 0.f, gy * grid->cellSize };
                currPath = grid->findPath(terminator->pos, endPos);
            }
            if (IsMouseButtonPressed(MOUSE_BUTTON_MIDDLE)) {
                startPos = { gx * grid->cellSize, 0.f, gy * grid->cellSize };
                currPath = grid->findPath(terminator->pos, endPos);
            }
        }
        else {
            hoveredCell = { -1, -1 };
        }
    }

    if (useAI) {
        aiModel->eval();
        torch::NoGradGuard nograd;
        torch::Tensor input = getGridTensor(terminator->pos, endPos);
        torch::Tensor output = aiModel->forward(input);
        int64_t act = output.argmax(1).item<int64_t>();
        Vector3 nextTarget = terminator->pos;
        switch (act) {
        case 0:
            nextTarget.z += grid->cellSize;
            break;
        case 1:
            nextTarget.z -= grid->cellSize;
            break;
        case 2:
            nextTarget.x += grid->cellSize;
            break;
        case 3:
            nextTarget.x -= grid->cellSize;
            break;
        }
        int nx = round(nextTarget.x / grid->cellSize);
        int nz = round(nextTarget.z / grid->cellSize);
        Node* nextNode = grid->getNode(nx, nz);
        if (nextNode && nextNode->walkable) {
            terminator->update(nextTarget, true, dt);
        }
        else {
            terminator->update(terminator->pos, false, dt);
        }
    }
    else syncTerminatorWithPath(dt);
}

void GameScene::onEnter() {
    initCamera();
    grid = new NavigationGrid(15, 15, 1.5f);
    terminator = std::make_shared<Terminator>();
    aiModel = std::make_shared<PathNet>();
    optimizer = std::make_shared<torch::optim::Adam>(aiModel->parameters(), torch::optim::AdamOptions(0.001));
    try {
        torch::load(aiModel, "PathNet.ai");
    }
    catch (...) {
        std::cerr << "Не удалось загрузить модель!\n";
    }
}

void GameScene::onExit() {

}

GameScene::~GameScene() {
    this->onExit();
}

GameScene::GameScene() {
    this->onEnter();
}

torch::Tensor GameScene::getGridTensor(Vector3 a, Vector3 b)
{
    auto tensor = torch::zeros({ 1, 3, 15 * 15 });
    for (size_t y = 0; y < grid->height; y++) {
        for (size_t x = 0; x < grid->width; x++) {
            if (!grid->getNode(x, y)->walkable) {
                tensor[0][0][y][x] = 1;
            }
        }
    }
    int ax = round(a.x / grid->cellSize);
    int ay = round(a.z / grid->cellSize);
    if (ax >= 0 && ax < grid->width && ay >= 0 && ay < grid->height)
    {
        tensor[0][1][ay][ax] = 1;
    }
    int ex = round(b.x / grid->cellSize);
    int ey = round(b.z / grid->cellSize);
    if (ex >= 0 && ex < grid->width && ey >= 0 && ey < grid->height)
    {
        tensor[0][2][ay][ax] = 1;
    }
    return tensor;
}

void GameScene::collectDataFromAStar()
{
    if (currPath.size() < 1)return;
    torch::Tensor input = getGridTensor(terminator->pos, endPos);
    Vector3 next = currPath[0];
    int64_t act = -1;
    float dx = next.x - terminator->pos.x;
    float dz = next.z - terminator->pos.z;
    if (dz > 0.5) act = 0;
    else if (dz < -0.5) act = 1;
    if (dx > 0.5) act = 2;
    else if (dx < -0.5) act = 3;
    if (act != -1) {
        dataset.push_back({ input, act });
    }
    if (dataset.size() > 2000) dataset.erase(dataset.begin());
}

void GameScene::syncTerminatorWithPath(float dt) {
    if (!currPath.empty()) {
        Vector3 nextNode(currPath[0]);
        if (Vector3Distance(terminator->pos, nextNode) < 1) {
            currPath.erase(currPath.begin());
        }
        terminator->update(nextNode, true, dt);
    }
}

void GameScene::trainStep() {
    if (dataset.size() < 32) {
        return;
    }
    aiModel->train();
    optimizer->zero_grad();
    std::vector<torch::Tensor> inputs;
    std::vector<int64_t> targets;
    for (size_t i = 0; i < 32; i++) {
        int idx = GetRandomValue(0, dataset.size() - 1);
        inputs.push_back(dataset[idx].input);
        targets.push_back(dataset[idx].action);
    }
    torch::Tensor bIn = torch::cat(inputs, 0);
    torch::Tensor bTarget = torch::tensor(targets, torch::kLong);
    torch::Tensor prediction = aiModel->forward(bIn);
    torch::Tensor loss = torch::nll_loss(prediction, bTarget);
    loss.backward();
    optimizer->step();
}
