#ifndef _WIZARD_ENEMY_H_
#define _WIZARD_ENEMY_H_

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

class WizardEnemy : public Object {
    private:
        static EntityAttributes wizardsAttributes;

        float hp;
        Sprite * sprite;
        Vector * speed;
        Player * player;
        int distance;
    public:
        WizardEnemy(Player * p);
        ~WizardEnemy();
        
        static void UpdateWaveAttributes();
        void OnCollision(Object* obj);
        void Update();
        void Draw();
}; 

inline void WizardEnemy::Draw()
{ sprite->Draw(x, y, Layer::LOWER, scale, rotation); }

#endif