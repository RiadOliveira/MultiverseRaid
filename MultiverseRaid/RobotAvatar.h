#ifndef _ROBOT_AVATAR_H_
#define _ROBOT_AVATAR_H_

#include "Types.h"
#include "Avatar.h"
#include "RobotDrone.h"

class RobotAvatar : public Avatar {
    private:
        RobotDrone* drone = nullptr;

        void HandleBasicAttack(Object* obj);
        void HandleUlt();
    public:
        RobotAvatar();
        ~RobotAvatar();

        void HandleSelectAvatar();
        void HandleUnselectAvatar();
}; 

#endif