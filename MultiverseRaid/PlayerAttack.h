#ifndef _PLAYER_ATTACK_H_
#define _PLAYER_ATTACK_H_

#include "Object.h"

class PlayerAttack : public Object {
    protected:
        uint damageType;
    public:
        PlayerAttack();
        virtual ~PlayerAttack();
        
        virtual void Update() = 0;
        virtual void Draw() = 0;
};

#endif