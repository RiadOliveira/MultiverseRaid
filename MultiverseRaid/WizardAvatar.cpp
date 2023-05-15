#include "WizardAvatar.h"
#include "WizardAttack.h"
#include "Random.h"
#include "MultiverseRaid.h"

WizardAvatar::WizardAvatar(): selectedTheme(WIZARD_THEME) {
    avatarType = WIZARD;
    basicAttackCooldown = 2.0f;
}

WizardAvatar::~WizardAvatar() {
    MultiverseRaid::audio->Stop(selectedTheme);
    MultiverseRaid::audio->Stop(FIRE_BALL);

    if(selectedTheme == WIZARD_RARE_THEME) {
        ACTIVE_TIME_LIMIT = DEFAULT_ACTIVE_TIME_LIMIT;
    }
}

void WizardAvatar::HandleSelectAvatar() {
    thunderStorm = new WizardThunderStorm();
    MultiverseRaid::scene->Add(thunderStorm, STATIC);

    RandI randomTheme{0, 9};
    bool rareTheme = randomTheme.Rand() == 0;
    
    if(rareTheme) {
        selectedTheme = WIZARD_RARE_THEME;
        ACTIVE_TIME_LIMIT = 139.0f;
    } else selectedTheme = WIZARD_THEME;

    MultiverseRaid::audio->Play(selectedTheme, true);
}

void WizardAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(thunderStorm, STATIC);
    MultiverseRaid::audio->Stop(selectedTheme);

    if(selectedTheme == WIZARD_RARE_THEME) {
        ACTIVE_TIME_LIMIT = DEFAULT_ACTIVE_TIME_LIMIT;
    }
}

void WizardAvatar::HandleBasicAttack(Object* obj) {
    WizardAttack* attack = new WizardAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, STATIC);
    MultiverseRaid::audio->Play(FIRE_BALL);
}

void WizardAvatar::HandleUlt() {
}
