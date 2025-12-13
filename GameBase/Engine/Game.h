//
// Created by Arsen on 23.11.2025.
//


#ifndef MY_APPLICATION_GAME_H

#define MY_APPLICATION_GAME_H
#include <string>
#include <vector>
#include "Scene/Scene.h"

#include "../External/raygui/raygui.h"
#include "Entity/Player.h"
#include <memory>
enum GameState{
    MAIN_MENU,
    IN_GAME
};

// class Player;

class Game {
private:
    signed long long windowX, windowY;
    std::string name;
    Font font;
    GameState currState;
    std::unique_ptr<Scene> currScene;
    std::unique_ptr<Player> player;
    void init();
public:

    explicit Game();
    void run();
    void setScene(Scene* _new){
        currScene.reset(_new);
    }
    Scene* getScene(){
        return currScene.get();
    }
    int* getCompleteCodepoints(int* );
    void loadResource();
    Font* getFont(){return &this->font;}
    void changeScene(GameState state);
    Player& getPlayer(){ return *player; }
};


#endif //MY_APPLICATION_GAME_H
