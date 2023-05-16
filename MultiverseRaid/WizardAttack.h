#ifndef _WIZARD_ATTACK_H_
#define _WIZARD_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "Attack.h"
#include "TileSet.h"
#include "Vector.h"
#include "Animation.h"

class WizardAttack : public Attack {
    private:
        TileSet* fireBall = nullptr;
        Animation* animation = nullptr;

        Vector speed;
    public:
        WizardAttack(Point* playerPoint, float angle);
        ~WizardAttack();

        void Update();
        void Draw();
};

inline void WizardAttack::Draw() {
    animation->Draw(x, y, z, 2.8f, rotation);
}

#endif