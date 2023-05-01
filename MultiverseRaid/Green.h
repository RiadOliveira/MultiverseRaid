#ifndef _GREEN_H_
#define _GREEN_H_

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

class Green : public Object
{
private:
    Sprite * sprite;
    Vector * speed;
    Player * player;
    int distance;
    
public:
    Green(Player * p);
    ~Green();
    
    void OnCollision(Object* obj);
    void Update();
    void Draw();
}; 

inline void Green::Draw()
{ sprite->Draw(x, y, Layer::LOWER, scale, rotation); }

#endif