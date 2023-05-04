#include "Avatar.h"
#include "MultiverseRaid.h"
#include "math.h"

const float Avatar::ALLOW_SWITCH_TIME = 10.0f;
const float Avatar::ACTIVE_TIME_LIMIT = 30.0f;

bool Avatar::canSwitchAvatar = false;
bool Avatar::reachedActiveTimeLimit = false;

Timer* Avatar::activeTimeTimer = new Timer();
Timer* Avatar::basicAttackTimer = new Timer();

Avatar::Avatar() {
    BBox(new Circle(290.0f));
    activeTimeTimer->Start();
    basicAttackTimer->Start();

    type = AVATAR;
}

Avatar::~Avatar() {
}

void Avatar::OnCollision(Object* obj) {
    uint type = obj->Type();
    if(type != ENEMY) return;

    if(basicAttackTimer->Elapsed() >= basicAttackCooldown) {
        HandleBasicAttack(obj);
        basicAttackTimer->Reset();
        BBox()->ScaleTo(0.0f);
    }
}

void Avatar::Update() {
    Player * player = MultiverseRaid::player;
    MoveTo(player->X(), player->Y());
    HandleUlt();

    if(basicAttackTimer->Elapsed() >= basicAttackCooldown) {
        BBox()->ScaleTo(min(BBox()->Scale() + 0.1f, 1.0f));
    }

    if(!canSwitchAvatar && activeTimeTimer->Elapsed() >= ALLOW_SWITCH_TIME) {
        canSwitchAvatar = true;
    }
    if(!reachedActiveTimeLimit && activeTimeTimer->Elapsed() >= ACTIVE_TIME_LIMIT) {
        reachedActiveTimeLimit = true;
    }
}

void Avatar::Draw() {
}