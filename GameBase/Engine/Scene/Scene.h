//
// Created by Arsen on 23.11.2025.
//

class Game;
#ifndef MY_APPLICATION_SCENE_H
#define MY_APPLICATION_SCENE_H


class Scene {
private:
    Game* buffer;
public:
    virtual ~Scene() = default;
    virtual void update(Game*, float) = 0;
    virtual void draw(Game*) = 0;
    virtual void onEnter() = 0;
    virtual void onExit() = 0;
};


#endif //MY_APPLICATION_SCENE_H
