#include "RobotAvatar.h"
#include "RobotAttack.h"
#include "MultiverseRaid.h"

RobotAvatar::RobotAvatar() {
    avatarType = ROBOT;
    basicAttackCooldown = 2.5f;
}

RobotAvatar::~RobotAvatar() {
    MultiverseRaid::audio->Stop(ROBOT_THEME);
    MultiverseRaid::audio->Stop(LASER_BEAM);
}

void RobotAvatar::HandleSelectAvatar() {
    drone = new RobotDrone();
    MultiverseRaid::scene->Add(drone, STATIC);
    MultiverseRaid::audio->Play(ROBOT_THEME, true);
}

void RobotAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(drone, STATIC);
    MultiverseRaid::audio->Stop(ROBOT_THEME);
}

void RobotAvatar::HandleBasicAttack(Object* obj) {
    RobotAttack* attack = new RobotAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, STATIC);
    MultiverseRaid::audio->Play(LASER_BEAM);
}

void RobotAvatar::HandleUlt() {
}
