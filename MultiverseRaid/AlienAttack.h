#ifndef _ALIEN_ATTACK_H_
#define _ALIEN_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "Attack.h"
#include "TileSet.h"
#include "Vector.h"
#include "Animation.h"

class AlienAttack : public Attack {
    private:
        TileSet* blackHole = nullptr;
        Animation* animation = nullptr;

        Vector speed;
    public:
        AlienAttack(float damage, Object* target);
        ~AlienAttack();

        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

inline void AlienAttack::Draw() {
    animation->Draw(x, y, z, scale - 0.18f, rotation);
}

#endif