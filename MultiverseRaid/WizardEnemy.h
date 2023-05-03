#ifndef _WIZARD_ENEMY_H_
#define _WIZARD_ENEMY_H_

#include "Enemy.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

class WizardEnemy : public Enemy {
    private:
        static EntityAttributes wizardsAttributes;
    public:
        WizardEnemy();
        ~WizardEnemy();
        
        static void UpdateWaveAttributes();
        void OnCollision(Object* obj);
        void Update();
};

#endif