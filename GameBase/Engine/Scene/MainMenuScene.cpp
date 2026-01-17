//
// Created by Arsen on 23.11.2025.
//

#include "MainMenuScene.h"
#include "../Game.h"

void MainMenuScene::drawUI(Game *game) {
    int width = GetScreenWidth();
    int height = GetScreenHeight();

    const float defButtonWidth = 500;
    const float defButtonHeight = 100;
    float buttonX = (width - defButtonWidth) / 2;
    float buttonY = (height * 0.45);
    float spacing = 120;

    //DrawCircle(100, 100, 60, Color{0, 0, 0, 255});

    if(GuiButton(Rectangle{buttonX, buttonY, defButtonWidth, defButtonHeight}, "START")){
        game->changeScene(GameState::IN_GAME);
    }
    buttonY += spacing;
    if(GuiButton(Rectangle{buttonX, buttonY, defButtonWidth, defButtonHeight}, "EXIT")){
        CloseWindow();
    }

}

void MainMenuScene::onExit() {

}

void MainMenuScene::update(Game *game, float dt) {

}

void MainMenuScene::onEnter() {

}

void MainMenuScene::draw(Game *game) {
    ClearBackground(Color{1, 1, 255, 255});
    this->drawUI(game);
}
