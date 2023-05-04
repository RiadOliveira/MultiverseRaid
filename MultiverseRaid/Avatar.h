#ifndef _AVATAR_H_
#define _AVATAR_H_

#include "Types.h"
#include "Object.h"
#include "Timer.h"

enum AvatarType { WIZARD, ROBOT, ALIEN };

class Avatar : public Object {
    protected:
        const static float ALLOW_SWITCH_TIME;
        const static float ACTIVE_TIME_LIMIT;

        uint avatarType = 0;
        float basicAttackCooldown = 0.0f;
        
        static bool canSwitchAvatar;
        static bool reachedActiveTimeLimit;

        static Timer* basicAttackTimer;
        static Timer* activeTimeTimer;
        virtual void HandleBasicAttack(Object* obj) = 0;
        virtual void HandleUlt() = 0;
    public:
        Avatar();
        virtual ~Avatar();

        static void ResetActiveTimeTimer();
        static bool CanSwitchAvatar();
        static bool ReachedActiveTimeLimit();

        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

inline void Avatar::ResetActiveTimeTimer() { activeTimeTimer->Reset(); }
inline bool Avatar::CanSwitchAvatar() { return canSwitchAvatar; }
inline bool Avatar::ReachedActiveTimeLimit() { return reachedActiveTimeLimit; }

#endif