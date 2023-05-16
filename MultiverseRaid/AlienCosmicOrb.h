#ifndef _ALIEN_COSMIC_ORB_H_
#define _ALIEN_COSMIC_ORB_H_

#include "Types.h"
#include "Sprite.h"
#include "Attack.h"
#include "TileSet.h"
#include "Vector.h"
#include "Animation.h"

class AlienCosmicOrb : public Attack {
    private:
        Sprite* sprite;
        Vector speed;
    public:
        AlienCosmicOrb(
            Image* cosmicOrb, float damage,
            float playerAngle
        );
        ~AlienCosmicOrb();

        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

inline void AlienCosmicOrb::Draw() {
    sprite->Draw(x, y, z, 0.14f, rotation);
}

#endif