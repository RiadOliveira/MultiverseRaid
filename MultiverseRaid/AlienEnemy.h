#ifndef _ALIEN_ENEMY_H_
#define _ALIEN_ENEMY_H_

#include "Object.h"    
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"
#include "Timer.h"

class AlienEnemy : public Object {
    private:
        static EntityAttributes aliensAttributes;

        float hp;
        Timer * attackSpeedTimer;
        Sprite * sprite;
        Vector * speed;
    public:
        AlienEnemy();
        ~AlienEnemy();
        
        static void UpdateWaveAttributes();
        void OnCollision(Object* obj);
        void Update();
        void Draw();
}; 

#endif