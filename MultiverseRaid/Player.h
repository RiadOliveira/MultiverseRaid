#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "Object.h"
#include "Sprite.h"
#include "Vector.h"
#include "Particles.h"

class Player : public Object
{
private:
    Sprite * sprite;
    Particles * tail;

public:
    Vector * speed;

    Player();
    ~Player();
    
    void Move(Vector && v);
    void Update();
    void Draw();
}; 

#endif