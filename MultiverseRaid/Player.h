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
        AvatarType selectedAvatar;

        SpriteState spriteState;
        EntityAttributes attributes;
        uint level;

        void HandleMovement();
        void InitializeAttributes();
    public:
        Player();
        ~Player();
        
        float Hp();
        bool isDead();
        void ApplyDamage(float damage);

        void LevelUp();
        void Update();
        void Draw();
};

inline float Player::Hp() {
    return attributes.hp;
}

inline bool Player::isDead() {
    return attributes.hp <= 0;
}

inline void Player::ApplyDamage(float damage) {
    attributes.hp -= damage;
    if(attributes.hp < 0) attributes.hp = 0;
}

#endif