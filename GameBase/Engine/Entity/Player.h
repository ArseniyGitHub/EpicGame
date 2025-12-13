//
// Created by Arsen on 23.11.2025.
//

#ifndef MY_APPLICATION_PLAYER_H
#define MY_APPLICATION_PLAYER_H
#include "Entity.h"

//class Entity;

class Player : public Entity {
private:
public:
    Vector3 getPos(){ return this->pos; }
    Player(Vector3 pos, Vector2 size, Color clr) {
        this->pos = pos;
        this->size = size;
        this->clr = clr;
    }
    Player(){}
    ~Player(){}
    virtual void update(Game*, float) ;
    virtual void draw(Game*);
};


#endif //MY_APPLICATION_PLAYER_H
