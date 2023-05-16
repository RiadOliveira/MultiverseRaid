#include "AlienAvatar.h"
#include "AlienAttack.h"
#include "MultiverseRaid.h"

AlienAvatar::AlienAvatar() {
    avatarType = ALIEN;
    basicAttackCooldown = 3.0f;

    tileSet = new TileSet(
        "Resources/Alien/AlienAvatar.png",
        250, 300, 4, 8
    );
    animation = new Animation(tileSet, 0.25f, true);

    uint rightSequence[4] = { 0, 1, 2, 3 };
    animation->Add(RIGHT, rightSequence, 4);

    uint leftSequence[4] = { 7, 6, 5, 4 };
    animation->Add(LEFT, leftSequence, 4);
}

AlienAvatar::~AlienAvatar() {
    MultiverseRaid::audio->Stop(ALIEN_THEME);
    MultiverseRaid::audio->Stop(BLACK_HOLE);

    if(cosmicOrbImage != nullptr) delete cosmicOrbImage;
    if(cosmicOrbs != nullptr) delete[] cosmicOrbs;
}

void AlienAvatar::HandleSelectAvatar() {
    uint gameWave = MultiverseRaid::gameWave - 1;
    orbsQuantity = min(max(gameWave - (gameWave % 3), 2), 5);

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
