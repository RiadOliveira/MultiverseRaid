#ifndef _ORANGE_H_
#define _ORANGE_H_

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

class Orange : public Object
{
private:
    Sprite * sprite;
    Vector * speed;
    Player * player;
    Particles * tail;
    float multiplier;
    
public:
    Orange(Player * p);
    ~Orange();
    
    void OnCollision(Object* obj);
    void Update();
    void Draw();
}; 

#endif