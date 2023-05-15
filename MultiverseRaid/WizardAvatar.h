#ifndef _WIZARD_AVATAR_H_
#define _WIZARD_AVATAR_H_

#include "Types.h"
#include "WizardThunderStorm.h"
#include "Timer.h"
#include "Avatar.h"

class WizardAvatar : public Avatar {
    private:
        Timer* timeStopper = nullptr;

        WizardThunderStorm* thunderStorm = nullptr;
        uint selectedTheme;

        void LegendaryMode(bool activate);
        void HandleBasicAttack(Object* obj);
        void HandleUlt();
    public:
        static bool legendaryMode;
        static bool timeIsStopped;

        WizardAvatar();
        ~WizardAvatar();

        void HandleSelectAvatar();
        void HandleUnselectAvatar();
}; 

#endif