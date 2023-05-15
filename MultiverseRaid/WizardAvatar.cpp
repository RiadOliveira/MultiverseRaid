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
    MultiverseRaid::scene->Add(thunderStorm, STATIC);
}

void WizardAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(thunderStorm, STATIC);
}

void WizardAvatar::HandleBasicAttack(Object* obj) {
    WizardAttack* attack = new WizardAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, STATIC);
    MultiverseRaid::audio->Play(FIRE_BALL);
}

void WizardAvatar::HandleUlt() {
}
