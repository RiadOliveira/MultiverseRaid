#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "EntityAttributes.h"
#include "Object.h"
#include "Sprite.h"
#include "Avatar.h"

enum SpriteState { LEFT, RIGHT };

class Player : public Object {
    private:
        Sprite * sprite;
        Avatar ** avatars;
        uint selectedAvatar;

        SpriteState spriteState;
        EntityAttributes attributes;
        uint level;

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
        SpriteState SpriteState();

        void ResetAttributes();
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

inline SpriteState Player::SpriteState() { return spriteState; }

#endif