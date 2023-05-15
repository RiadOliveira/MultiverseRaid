#include "AlienAvatar.h"
#include "AlienAttack.h"
#include "MultiverseRaid.h"

AlienAvatar::AlienAvatar() {
    avatarType = ALIEN;
    basicAttackCooldown = 3.0f;
}

AlienAvatar::~AlienAvatar() {
    MultiverseRaid::audio->Stop(ALIEN_THEME);
    MultiverseRaid::audio->Stop(BLACK_HOLE);

    if(cosmicOrbImage != nullptr) delete cosmicOrbImage;
    if(cosmicOrbs != nullptr) delete[] cosmicOrbs;
}

void AlienAvatar::HandleSelectAvatar() {
    orbsQuantity = 3;
    cosmicOrbImage = new Image("Resources/Alien/AlienCosmicOrb.png");
    cosmicOrbs = new AlienCosmicOrb*[orbsQuantity];

    float orbsAngle = 360.0f / orbsQuantity;
    for(uint ind=0 ; ind<orbsQuantity ; ind++) {
        cosmicOrbs[ind] = new AlienCosmicOrb(
            cosmicOrbImage, 8.0f, orbsAngle * ind
        );
        MultiverseRaid::scene->Add(cosmicOrbs[ind], STATIC);
    }
    MultiverseRaid::audio->Play(ALIEN_THEME, true);
}

void AlienAvatar::HandleUnselectAvatar() {
    for(uint ind=0 ; ind<orbsQuantity ; ind++) {
        MultiverseRaid::scene->Delete(cosmicOrbs[ind], STATIC);
    }
    MultiverseRaid::audio->Stop(ALIEN_THEME);

    delete cosmicOrbImage; cosmicOrbImage = nullptr;
    delete[] cosmicOrbs; cosmicOrbs = nullptr;
}

void AlienAvatar::HandleBasicAttack(Object* obj) {
    AlienAttack* attack = new AlienAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, STATIC);
    MultiverseRaid::audio->Play(BLACK_HOLE);
}

void AlienAvatar::HandleUlt() {
}
