#ifndef _ALIEN_AVATAR_H_
#define _ALIEN_AVATAR_H_

#include "Types.h"
#include "Avatar.h"
#include "AlienCosmicOrb.h"

class AlienAvatar : public Avatar {
    private:
        Image* cosmicOrbImage = nullptr;
        AlienCosmicOrb** cosmicOrbs = nullptr;
        uint orbsQuantity = 0;

        void HandleBasicAttack(Object* obj);
        void HandleUlt();
    public:
        AlienAvatar();
        ~AlienAvatar();

        void HandleSelectAvatar();
        void HandleUnselectAvatar();
}; 

#endif