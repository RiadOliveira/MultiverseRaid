#ifndef _ALIEN_AVATAR_H_
#define _ALIEN_AVATAR_H_

#include "Types.h"
#include "Avatar.h"

class AlienAvatar : public Avatar {
    private:
        void HandleBasicAttack(Object* obj);
        void HandleUlt();
    public:
        AlienAvatar();
        ~AlienAvatar();

        void HandleSelectAvatar();
        void HandleUnselectAvatar();
}; 

#endif