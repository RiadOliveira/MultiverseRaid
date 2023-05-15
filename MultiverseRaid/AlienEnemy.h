#ifndef _ALIEN_ENEMY_H_
#define _ALIEN_ENEMY_H_

#include "Enemy.h"    
#include "Types.h"
#include "Sprite.h"
#include "Player.h"
#include "Timer.h"
#include "Vector.h"

class AlienEnemy : public Enemy {
    private:
        static EntityAttributes aliensAttributes;
    public:
        static EntityAttributes defaultAttributes;

        AlienEnemy();
        ~AlienEnemy();
        
        static void ResetWaveAttributes();
        static void UpdateWaveAttributes();

        void OnCollision(Object* obj);
        void Update();
        void Draw();
}; 

inline void AlienEnemy::Draw() { DefaultDraw(0.3f); }

#endif