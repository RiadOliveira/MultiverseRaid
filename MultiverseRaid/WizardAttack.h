#ifndef _WIZARD_ATTACK_H_
#define _WIZARD_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "PlayerAttack.h"
#include "TileSet.h"
#include "Vector.h"
#include "Animation.h"

class WizardAttack : public PlayerAttack {
    private:
        TileSet* fireBall = nullptr;
        Animation* animation = nullptr;

        Vector speed;
    public:
        WizardAttack(float damage, Object* target);
        ~WizardAttack();

        void Update();
        void Draw();
};

inline void WizardAttack::Draw() {
    animation->Draw(x, y, z, 2.8f, rotation);
}

#endif