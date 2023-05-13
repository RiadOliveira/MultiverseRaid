#ifndef _WIZARD_THUNDER_STORM_H_
#define _WIZARD_THUNDER_STORM_H_

#include "Types.h"
#include "Object.h"
#include "Timer.h"

class WizardThunderStorm : public Object {
    private:
        Timer* cooldownTimer = nullptr;
    public:
        WizardThunderStorm();
        ~WizardThunderStorm();

        void OnCollision(Object* obj);
        void Update();
        void Draw();
};

#endif