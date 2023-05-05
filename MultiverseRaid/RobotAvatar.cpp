#include "RobotAvatar.h"
#include "RobotAttack.h"
#include "MultiverseRaid.h"

RobotAvatar::RobotAvatar() {
    avatarType = ROBOT;
    basicAttackCooldown = 1.0f;
}

RobotAvatar::~RobotAvatar() {
}

void RobotAvatar::HandleSelectAvatar() {
    drone = new RobotDrone();
    MultiverseRaid::scene->Add(drone, MOVING);
}

void RobotAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(drone, MOVING);
}

void RobotAvatar::HandleBasicAttack(Object* obj) {
    RobotAttack* attack = new RobotAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, MOVING);
}

void RobotAvatar::HandleUlt() {
}
