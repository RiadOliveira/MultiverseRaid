#ifndef _HUD_H_
#define _HUD_H_

#include "Object.h"
#include "Sprite.h"
#include "Font.h"
#include <sstream>
using std::stringstream;

class Hud : public Object
{
private:
    Font * font = nullptr;
    Font * bold = nullptr;
    Sprite * infoBox = nullptr;
    Sprite * keyMap = nullptr;
    stringstream text;

public:
    Hud();
    ~Hud();

    void Update();
    void Draw();
};

#endif