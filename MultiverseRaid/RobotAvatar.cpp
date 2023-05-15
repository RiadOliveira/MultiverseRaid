#include "RobotAvatar.h"
#include "RobotAttack.h"
#include "MultiverseRaid.h"

RobotAvatar::RobotAvatar() {
    avatarType = ROBOT;
    basicAttackCooldown = 2.5f;
}

RobotAvatar::~RobotAvatar() {
}

void RobotAvatar::HandleSelectAvatar() {
    drone = new RobotDrone();
    MultiverseRaid::scene->Add(drone, STATIC);
}

void RobotAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(drone, STATIC);
}

void RobotAvatar::HandleBasicAttack(Object* obj) {
    RobotAttack* attack = new RobotAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, STATIC);
}

void RobotAvatar::HandleUlt() {
}
