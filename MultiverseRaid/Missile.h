#ifndef _MISSILE_H_
#define _MISSILE_H_

#include "Vector.h"
#include "Object.h"
#include "Sprite.h"
#include "Player.h" 

class Missile : public Object
{
private:
    const float MaxDistance = 4406;
    const float BaseVolume = 0.8f;

    static Player* & player;
    Sprite * sprite;
    Vector speed;
    
public:
    Missile();
    ~Missile();

    Vector& Speed();
    void Update();
    void Draw();
}; 

inline Vector& Missile::Speed()
{ return speed; }

inline void Missile::Draw()
{ sprite->Draw(x, y, Layer::UPPER, scale, rotation); }

#endif