#include "WizardAvatar.h"
#include "WizardAttack.h"
#include "MultiverseRaid.h"

WizardAvatar::WizardAvatar() {
    avatarType = WIZARD;
    basicAttackCooldown = 3.0f;
}

WizardAvatar::~WizardAvatar() {
}

void WizardAvatar::HandleSelectAvatar() {
}

void WizardAvatar::HandleUnselectAvatar() {
}

void WizardAvatar::HandleBasicAttack(Object* obj) {
    WizardAttack* attack = new WizardAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, MOVING);
}

void WizardAvatar::HandleUlt() {
}
