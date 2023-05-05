#ifndef _WIZARD_AVATAR_H_
#define _WIZARD_AVATAR_H_

#include "Types.h"
#include "Avatar.h"

class WizardAvatar : public Avatar {
    private:
        void HandleBasicAttack(Object* obj);
        void HandleUlt();
    public:
        WizardAvatar();
        ~WizardAvatar();

        void HandleSelectAvatar();
        void HandleUnselectAvatar();
}; 

#endif