#include "RobotAvatar.h"
#include "RobotAttack.h"
#include "MultiverseRaid.h"

RobotAvatar::RobotAvatar() {
    avatarType = ROBOT;
    basicAttackCooldown = 1.0f;
}

RobotAvatar::~RobotAvatar() {
}

void RobotAvatar::HandleBasicAttack(Object* obj) {
    RobotAttack* attack = new RobotAttack(
        x, y, obj
    );
    MultiverseRaid::scene->Add(attack, MOVING);
}

void RobotAvatar::HandleUlt() {

}
