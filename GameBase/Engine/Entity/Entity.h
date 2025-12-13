//
// Created by Arsen on 23.11.2025.
//

#ifndef MY_APPLICATION_ENTITY_H
#define MY_APPLICATION_ENTITY_H
#include <raylib.h>
#include <raymath.h>


class Game;

class Entity {
protected:
    Vector3 pos;
    Vector3 velocity;
    Vector2 size;
    Vector2 rotation;
    Color clr;
public:
    virtual void update(Game*, float) = 0;
    virtual void draw(Game*) = 0;
    virtual ~Entity();
};


#endif //MY_APPLICATION_ENTITY_H
