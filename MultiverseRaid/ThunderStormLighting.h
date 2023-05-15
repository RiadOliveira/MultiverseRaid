#ifndef _THUNDER_STORM_LIGHTING_H_
#define _THUNDER_STORM_LIGHTING_H_

#include "Types.h"
#include "Sprite.h"
#include "Attack.h"
#include "TileSet.h"
#include "Animation.h"

class ThunderStormLighting : public Attack {
    private:
        TileSet* lighting = nullptr;
        Animation* animation = nullptr;
    public:
        ThunderStormLighting(Point* target);
        ~ThunderStormLighting();

        void Update();
        void Draw();
};

inline void ThunderStormLighting::Draw() {
    animation->Draw(x, y - 181.5f, z, 1.0f, rotation);
}

#endif