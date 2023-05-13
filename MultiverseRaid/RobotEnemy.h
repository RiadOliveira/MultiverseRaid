#ifndef _ROBOT_ENEMY_H_
#define _ROBOT_ENEMY_H_

#include "Enemy.h"
#include "EntityAttributes.h"
#include "Types.h"
#include "Sprite.h"
#include "Player.h"
#include "Timer.h"
#include "Vector.h"

class RobotEnemy : public Enemy {
    private:
        static EntityAttributes robotsAttributes;
    public:
        RobotEnemy();
        ~RobotEnemy();
        
        static void UpdateWaveAttributes();
        void OnCollision(Object * obj);
        void Update();
        void Draw();
};

inline void RobotEnemy::Draw() {
    animation->Draw(x, y, Layer::LOWER, 0.25f, rotation);
}

#endif