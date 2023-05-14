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
    orbsQuantity = 2;
    cosmicOrbImage = new Image("Resources/Alien/AlienCosmicOrb.png");
    cosmicOrbs = new AlienCosmicOrb*[orbsQuantity];

    float orbsAngle = 360.0f / orbsQuantity;
    for(uint ind=0 ; ind<orbsQuantity ; ind++) {
        cosmicOrbs[ind] = new AlienCosmicOrb(
            cosmicOrbImage, 8.0f, orbsAngle * ind
        );
        MultiverseRaid::scene->Add(cosmicOrbs[ind], MOVING);
    }
}

void AlienAvatar::HandleUnselectAvatar() {
    for(uint ind=0 ; ind<orbsQuantity ; ind++) {
        MultiverseRaid::scene->Delete(cosmicOrbs[ind], MOVING);
    }

    delete cosmicOrbImage;
    delete[] cosmicOrbs;
}

void AlienAvatar::HandleBasicAttack(Object* obj) {
    AlienAttack* attack = new AlienAttack(8.0f, obj);
    MultiverseRaid::scene->Add(attack, MOVING);
}

void AlienAvatar::HandleUlt() {
}
