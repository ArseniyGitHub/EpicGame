//
// Created by Arsen on 23.11.2025.
//

#ifndef MY_APPLICATION_MAINMENUSCENE_H
#define MY_APPLICATION_MAINMENUSCENE_H
#include "Scene.h"


class MainMenuScene : public Scene {
private:
    void drawUI(Game*);
public:
    void draw(Game*);
    void update(Game*, float);
    void onEnter();
    void onExit();
};


#endif //MY_APPLICATION_MAINMENUSCENE_H
