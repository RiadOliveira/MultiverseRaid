#ifndef _ALIEN_AVATAR_H_
#define _ALIEN_AVATAR_H_

#include "Types.h"
#include "Avatar.h"

class AlienAvatar : Avatar {
    private:
        void PassiveUpdate();
        void PassiveDraw();

        void UltUpdate();
        void UltDraw();
    public:
        AlienAvatar();
        ~AlienAvatar();
}; 

#endif