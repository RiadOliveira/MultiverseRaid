#ifndef _WALLHIT_H_
#define _WALLHIT_H_

#include "Object.h"    
#include "Types.h"
#include "Particles.h"
#include "Missile.h"

class WallHit : public Object
{
private:
    Particles * sparks;
    
public:
    WallHit(float pX, float pY);
    ~WallHit();

    int  Size();
    void Update();
    void Draw();
}; 

inline int WallHit::Size()
{ return sparks->Size(); }

inline void WallHit::Draw()
{ sparks->Draw(Layer::MIDDLE, 0.0f); }

#endif