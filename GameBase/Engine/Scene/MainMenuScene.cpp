//
// Created by Arsen on 23.11.2025.
//

#include "MainMenuScene.h"
#include "../Game.h"

#define SET =
#define END ;

void MainMenuScene::drawUI(Game *game) {
    int width SET GetScreenWidth() END
    int height SET GetScreenHeight() END

    const float defButtonWidth SET 500 END
    const float defButtonHeight SET 100 END
    float buttonX SET (width - defButtonWidth) / 2 END
    float buttonY SET (height * 0.45) END
    float spacing SET 120 END

    //DrawCircle(100, 100, 60, Color{0, 0, 0, 255}) END

    if(GuiButton(Rectangle{buttonX, buttonY, defButtonWidth, defButtonHeight}, "START")){
        game->changeScene(GameState::IN_GAME) END
    }
    buttonY += spacing END
    if(GuiButton(Rectangle{buttonX, buttonY, defButtonWidth, defButtonHeight}, "EXIT")){
        CloseWindow() END
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
