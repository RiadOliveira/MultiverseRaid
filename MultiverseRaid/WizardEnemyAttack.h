#ifndef _WIZARD_ENEMY_ATTACK_H_
#define _WIZARD_ENEMY_ATTACK_H_

#include "Types.h"
#include "Sprite.h"
#include "Attack.h"
#include "Vector.h"
#include "Timer.h"
#include "WizardEnemy.h"

class WizardEnemyAttack : public Attack {
    private:
        Sprite* energyBall = nullptr;
        Vector speed;
    public:
        WizardEnemyAttack(float damage, WizardEnemy* origin);
        ~WizardEnemyAttack();

        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

inline void WizardEnemyAttack::Draw() {
    energyBall->Draw(x, y, z, 2.5f, rotation);
}

#endif