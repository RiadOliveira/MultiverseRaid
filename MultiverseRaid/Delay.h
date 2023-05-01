#ifndef _DELAY_H_
#define _DELAY_H_

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"

class Delay : public Object
{
private:
    Sprite * logo;
    Timer timer;
    bool notPlayed;

public:
    Delay();
    ~Delay();

    void Update();
    void Draw();
};

#endif