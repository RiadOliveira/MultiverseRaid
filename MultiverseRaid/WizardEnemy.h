#ifndef _WIZARD_ENEMY_H_
#define _WIZARD_ENEMY_H_

#include "Enemy.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

class WizardEnemy : public Enemy {
    private:
        static EntityAttributes defaultAttributes;
        static EntityAttributes wizardsAttributes;

        void HandleAttackPlayer();
    public:
        WizardEnemy();
        ~WizardEnemy();
        
        static void ResetWaveAttributes();
        static void UpdateWaveAttributes();
        
        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

inline void WizardEnemy::Draw() { DefaultDraw(0.25f); }

#endif