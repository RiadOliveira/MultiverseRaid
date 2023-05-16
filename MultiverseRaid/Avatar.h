#ifndef _AVATAR_H_
#define _AVATAR_H_

#include "Types.h"
#include "Object.h"
#include "Timer.h"
#include "TileSet.h"
#include "Animation.h"

enum AvatarType { WIZARD, ROBOT, ALIEN };

class Avatar : public Object {
    protected:
        const static float ALLOW_SWITCH_TIME;
        const static float DEFAULT_ACTIVE_TIME_LIMIT;
        static float ACTIVE_TIME_LIMIT;

        static bool canSwitchAvatar;
        static bool reachedActiveTimeLimit;

        TileSet* tileSet = nullptr;

        static Timer* basicAttackTimer;
        static Timer* activeTimeTimer;

        uint avatarType = 0;
        float basicAttackCooldown = 0.0f;
        
        virtual void HandleBasicAttack(Object* obj) = 0;
        virtual void HandleUlt() = 0;
    public:
        Animation* animation = nullptr;

        Avatar();
        virtual ~Avatar();

        static void ResetTimersData();
        static bool CanSwitchAvatar();
        static bool ReachedActiveTimeLimit();
        
        virtual void HandleSelectAvatar() = 0;
        virtual void HandleUnselectAvatar() = 0;

        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

inline void Avatar::ResetTimersData() { 
    basicAttackTimer->Reset(); activeTimeTimer->Reset();
    canSwitchAvatar = false; reachedActiveTimeLimit = false;
}
inline bool Avatar::CanSwitchAvatar() { return canSwitchAvatar; }
inline bool Avatar::ReachedActiveTimeLimit() { return reachedActiveTimeLimit; }

#endif