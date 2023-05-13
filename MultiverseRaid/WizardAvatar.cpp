#include "WizardAvatar.h"
#include "WizardAttack.h"
#include "MultiverseRaid.h"

WizardAvatar::WizardAvatar() {
    avatarType = WIZARD;
    basicAttackCooldown = 2.0f;
}

WizardAvatar::~WizardAvatar() {
}

void WizardAvatar::HandleSelectAvatar() {
    thunderStorm = new WizardThunderStorm();
    MultiverseRaid::scene->Add(thunderStorm, MOVING);
}

void WizardAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(thunderStorm, MOVING);
}

void WizardAvatar::HandleBasicAttack(Object* obj) {
    WizardAttack* attack = new WizardAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, MOVING);
}

void WizardAvatar::HandleUlt() {
}
