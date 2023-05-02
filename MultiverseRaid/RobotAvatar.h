#ifndef _ROBOT_AVATAR_H_
#define _ROBOT_AVATAR_H_

#include "Types.h"
#include "Avatar.h"

class RobotAvatar : Avatar {
    private:
        void PassiveUpdate();
        void PassiveDraw();

        void UltUpdate();
        void UltDraw();
    public:
        RobotAvatar();
        ~RobotAvatar();
}; 

#endif