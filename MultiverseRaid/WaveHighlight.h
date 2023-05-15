#ifndef _WAVE_HIGHLIGHT_H_
#define _WAVE_HIGHLIGHT_H_

#include "Object.h"
#include "Sprite.h"
#include "Timer.h"
#include "Font.h"
#include <sstream>
using std::stringstream;

class WaveHighlight : public Object {
    private:
        Font * font;
        Timer timer;
        stringstream text;
    public:
        WaveHighlight();
        ~WaveHighlight();

        void Update();
        void Draw();
};

#endif