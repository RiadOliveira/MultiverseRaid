#ifndef _ALIEN_COSMIC_ORB_H_
#define _ALIEN_COSMIC_ORB_H_

#include "Types.h"
#include "Sprite.h"
#include "PlayerAttack.h"
#include "TileSet.h"
#include "Vector.h"
#include "Animation.h"

class AlienCosmicOrb : public PlayerAttack {
    private:
        Sprite* sprite;
        Vector speed;
    public:
        AlienCosmicOrb(
            Image* cosmicOrb, float damage,
            float playerAngle
        );
        ~AlienCosmicOrb();

        void Update();
        void Draw();
};

inline void AlienCosmicOrb::Draw() {
    sprite->Draw(x, y, z, 0.15f, rotation);
}

#endif