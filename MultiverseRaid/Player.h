#ifndef _PLAYER_H_
#define _PLAYER_H_

#include "EntityAttributes.h"
#include "Object.h"
#include "Sprite.h"

enum SpriteState { LEFT, RIGHT };

class Player : public Object {
    private:
        Sprite * sprite;
        SpriteState spriteState;
        EntityAttributes attributes;
        uint level;

        void HandleMovement();
        void InitializeAttributes();
    public:
        Player();
        ~Player();
        
        void LevelUp();
        void Update();
        void Draw();
}; 

#endif