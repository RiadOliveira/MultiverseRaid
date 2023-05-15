#ifndef _ENEMY_H_
#define _ENEMY_H_

#include "Object.h"
#include "Types.h"
#include "Sprite.h"
#include "Player.h"
#include "Timer.h"
#include "Vector.h"
#include "Attack.h"
#include "TileSet.h"
#include "Animation.h"

class Enemy : public Object {
    protected:
        Timer* colorTimer = nullptr;
        Attack* lastAttackReceived = nullptr;

        uint enemyType = 0;
        float hp = 0.0f;

        TileSet* tileSet = nullptr;
        Animation* animation = nullptr;
        Vector* speed = nullptr;
        Timer* attackSpeedTimer = nullptr;
        Timer* damageReceiverTimer = nullptr;

        void HandleEntityCollision(Object* entity, float speed);
        void HandlePlayerCollision(float enemyDamage, float enemyAttackSpeed);
        void HandlePlayerAttackCollision(
            Attack* attack, float damageReduction
        );
        void DefaultDraw(float scale);
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

inline void Enemy::DefaultDraw(float scale = 1.0f) {
    Color animationColor;
    if(colorTimer == nullptr || colorTimer->Elapsed() > 0.25f) {
        animationColor = Color{1.0f, 1.0f, 1.0f, 1.0f};
    } else animationColor = Color{1.0f, 0.5f, 0.5f, 1.0f};

    animation->Draw(x, y, Layer::LOWER, scale, rotation, animationColor);
}

#endif