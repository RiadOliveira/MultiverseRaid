#ifndef _AVATAR_H_
#define _AVATAR_H_

#include "Types.h"

enum AvatarType { WIZARD, ROBOT, ALIEN };

class Avatar {
    protected:
        AvatarType type;

        virtual void PassiveUpdate() = 0;
        virtual void PassiveDraw() = 0;

        virtual void UltUpdate() = 0;
        virtual void UltDraw() = 0;
    public:
        Avatar();
        virtual ~Avatar();

        void Update();
        void Draw();
}; 

#endif