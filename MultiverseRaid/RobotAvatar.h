#ifndef _ROBOT_AVATAR_H_
#define _ROBOT_AVATAR_H_

#include "Types.h"
#include "Avatar.h"

class RobotAvatar : public Avatar {
    private:
        void HandleBasicAttack(Object* obj);
        void HandleUlt();
    public:
        RobotAvatar();
        ~RobotAvatar();
}; 

#endif