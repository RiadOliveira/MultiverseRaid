#ifndef _ROBOT_ENEMY_H_
#define _ROBOT_ENEMY_H_

#include "Object.h"
#include "EntityAttributes.h"
#include "Types.h"
#include "Sprite.h"
#include "Vector.h"
#include "Player.h"

class RobotEnemy : public Object {
    private:
        static EntityAttributes robotsAttributes;

        float hp;
        Sprite * sprite;
        Vector * speed;
        Player * player;
    public:
        RobotEnemy(Player * p);
        ~RobotEnemy();
        
        static void UpdateWaveAttributes();
        void OnCollision(Object * obj);
        void Update();
        void Draw();
}; 

inline void RobotEnemy::Draw()
{ sprite->Draw(x, y, Layer::LOWER, scale, rotation); }

#endif