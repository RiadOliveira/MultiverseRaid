#include "AlienAvatar.h"
#include "AlienAttack.h"
#include "MultiverseRaid.h"

AlienAvatar::AlienAvatar() {
    avatarType = ALIEN;
    basicAttackCooldown = 3.0f;
}

AlienAvatar::~AlienAvatar() {
}

void AlienAvatar::HandleSelectAvatar() {

}

void AlienAvatar::HandleUnselectAvatar() {

}

void AlienAvatar::HandleBasicAttack(Object* obj) {
    AlienAttack* attack = new AlienAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, MOVING);
}

void AlienAvatar::HandleUlt() {

}
