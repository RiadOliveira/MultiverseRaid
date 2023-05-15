#ifndef _ATTACK_H_
#define _ATTACK_H_

#include "Object.h"

class Attack : public Object {
    protected:
        uint damageType = 0;
        float damageTickTime = 0.0f;
        float damagePerTick = 0.0f;
    public:
        Attack();
        virtual ~Attack();

        uint DamageType();
        float DamageTickTime();
        float DamagePerTick();
        
        virtual void Update() = 0;
        virtual void Draw() = 0;
};

inline uint Attack::DamageType() { return damageType; };
inline float Attack::DamageTickTime() { return damageTickTime; };
inline float Attack::DamagePerTick() { return damagePerTick; }

#endif