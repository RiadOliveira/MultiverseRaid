#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Object.h"
#include "Types.h"
#include "Sprite.h"
#include "Player.h"
#include "Timer.h"
#include "Vector.h"
#include "PlayerAttack.h"
#include "TileSet.h"
#include "Animation.h"

class Enemy : public Object {
    protected:
        uint enemyType = 0;
        float hp = 0.0f;

        TileSet* tileSet = nullptr;
        Animation* animation = nullptr;
        Vector* speed = nullptr;
        Timer* attackSpeedTimer = nullptr;
        Timer* damageReceiverTimer = nullptr;

        void HandlePlayerCollision(float enemyDamage, float enemyAttackSpeed);
        void HandlePlayerAttackCollision(
            PlayerAttack* attack, float damageReduction
        );
    public:
        Enemy();
        virtual ~Enemy();
        
        void ApplyDamage(float damage);
        bool IsDead();

        virtual void OnCollision(Object * obj) = 0;
        virtual void Update() = 0;
        virtual void Draw() = 0;
};

inline void Enemy::ApplyDamage(float damage) {
    hp -= damage;
    if(hp < 0.0f) hp = 0.0f;
}

inline bool Enemy::IsDead() { return hp <= 0.0f; }

#endif