#ifndef _MAGENTA_H_
#define _MAGENTA_H_

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

class Magenta : public Object
{
private:
    Sprite * sprite;
    Vector * speed;
    Player * player;
    
public:
    Magenta(Player * p);
    ~Magenta();
    
    void OnCollision(Object * obj);
    void Update();
    void Draw();
}; 

inline void Magenta::Draw()
{ sprite->Draw(x, y, Layer::LOWER, scale, rotation); }

#endif