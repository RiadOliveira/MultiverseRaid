#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Object.h"
#include "Types.h"
#include "Sprite.h"
#include "Player.h"
#include "Timer.h"
#include "Vector.h"

class Enemy : public Object {
    protected:
        uint enemyType;

        float hp;
        Sprite * sprite;
        Vector * speed;
        Timer * attackSpeedTimer = nullptr;
    public:
        Enemy();
        virtual ~Enemy();
        
        virtual void OnCollision(Object * obj) = 0;
        virtual void Update() = 0;
        virtual void Draw();
}; 

inline void Enemy::Draw() {
    sprite->Draw(x, y, Layer::LOWER, scale, rotation);
}

#endif