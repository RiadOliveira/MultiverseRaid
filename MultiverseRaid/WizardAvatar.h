#ifndef _WIZARD_AVATAR_H_
#define _WIZARD_AVATAR_H_

#include "Types.h"
#include "Avatar.h"

class WizardAvatar : Avatar {
    private:
        void PassiveUpdate();
        void PassiveDraw();

        void UltUpdate();
        void UltDraw();
    public:
        WizardAvatar();
        ~WizardAvatar();
}; 

#endif