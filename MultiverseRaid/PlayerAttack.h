#ifndef _PLAYER_ATTACK_H_
#define _PLAYER_ATTACK_H_

#include "Object.h"

class PlayerAttack : public Object {
    protected:
        uint damageType = 0;
        float damageTickTime = 0.0f;
        float damagePerTick = 0.0f;
    public:
        PlayerAttack();
        virtual ~PlayerAttack();

        uint DamageType();
        float DamageTickTime();
        float DamagePerTick();
        
        virtual void Update() = 0;
        virtual void Draw() = 0;
};

inline uint PlayerAttack::DamageType() { return damageType; };
inline float PlayerAttack::DamageTickTime() { return damageTickTime; };
inline float PlayerAttack::DamagePerTick() { return damagePerTick; }

#endif