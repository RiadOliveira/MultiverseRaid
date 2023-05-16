#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "EntityAttributes.h"
#include "Object.h"
#include "Avatar.h"

class Player : public Object {
    private:
        Avatar ** avatars;
        uint selectedAvatar;

        uint tileSetState;
        EntityAttributes attributes;
        uint level;

        void SetAttributes();
        void HandleMovement();
        float GetSelectedAvatarDefenseValue();
        bool HasDisadvantageOnEnemyType(uint enemyType);
        float GetDamageReduction(uint damageReceivedType);
    public:
        Player();
        ~Player();
        
        float Hp();
        bool IsDead();
        void ApplyDamage(float damage, uint damageType);
        uint TileSetState();

        EntityAttributes Attributes();
        void LevelUp();
        void Update();
        void Draw();
};

inline float Player::Hp() {
    return attributes.hp;
}

inline bool Player::IsDead() {
    return attributes.hp <= 0.0f;
}

inline EntityAttributes Player::Attributes() {
    return attributes;
}

inline uint Player::TileSetState() { return tileSetState; }

#endif