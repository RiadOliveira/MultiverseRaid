#include "WizardAvatar.h"
#include "WizardAttack.h"
#include "MultiverseRaid.h"
#include "Random.h"

bool WizardAvatar::legendaryMode = false;
bool WizardAvatar::timeIsStopped = false;

WizardAvatar::WizardAvatar(): selectedTheme(WIZARD_THEME) {
    avatarType = WIZARD;
    basicAttackCooldown = 2.0f;

    tileSet = new TileSet(
        "Resources/Wizard/WizardAvatar.png",
        250, 300, 4, 8
    );
    animation = new Animation(tileSet, 0.25f, true);

    uint rightSequence[4] = { 0, 1, 2, 3 };
    animation->Add(RIGHT, rightSequence, 4);

    uint leftSequence[4] = { 7, 6, 5, 4 };
    animation->Add(LEFT, leftSequence, 4);
}

WizardAvatar::~WizardAvatar() {
    MultiverseRaid::audio->Stop(selectedTheme);
    MultiverseRaid::audio->Stop(FIRE_BALL);

    delete timeStopper;
    LegendaryMode(false);
}

void WizardAvatar::LegendaryMode(bool activate) {
    legendaryMode = activate;

    if(legendaryMode) {
        selectedTheme = WIZARD_LEGENDARY_THEME;
        basicAttackCooldown = 1.0f;
        ACTIVE_TIME_LIMIT = 139.0f;

        if(timeStopper != nullptr) delete timeStopper;
        timeStopper = new Timer();
        timeStopper->Start();
    } else {
        selectedTheme = WIZARD_THEME;
        basicAttackCooldown = 2.0f;
        ACTIVE_TIME_LIMIT = DEFAULT_ACTIVE_TIME_LIMIT;
        timeIsStopped = false;
    }
}

void WizardAvatar::HandleSelectAvatar() {
    thunderStorm = new WizardThunderStorm();
    MultiverseRaid::scene->Add(thunderStorm, STATIC);

    RandI randomTheme{0, 9};
    bool activateLegendaryMode = randomTheme.Rand() == 0;
    
    LegendaryMode(activateLegendaryMode);
    MultiverseRaid::audio->Play(selectedTheme, true);
}

void WizardAvatar::HandleUnselectAvatar() {
    MultiverseRaid::scene->Delete(thunderStorm, STATIC);
    MultiverseRaid::audio->Stop(selectedTheme);
    LegendaryMode(false);
}

void WizardAvatar::HandleBasicAttack(Object* obj) {
    Player* player = MultiverseRaid::player;
    Point* playerPoint = new Point(player->X(), player->Y());

    float angle = Line::Angle(*playerPoint, Point(obj->X(), obj->Y()));
    int fireBallQuantity = 1 + min((MultiverseRaid::gameWave - 1) / 3 * 2, 5);

    int angleModifier = 15 * (fireBallQuantity - 1) / 2;
    for(int ind=-angleModifier ; ind<=angleModifier ; ind += 15) {
         WizardAttack* attack = new WizardAttack(
            playerPoint, angle + ind
        );
        
        MultiverseRaid::scene->Add(attack, STATIC);
        MultiverseRaid::audio->Play(FIRE_BALL);
    }
    
    delete playerPoint;
}

void WizardAvatar::HandleUlt() {
    if(!legendaryMode) return;

    float elapsed = timeStopper->Elapsed();
    if(elapsed < 64.0f || elapsed >= 72.0f && !timeIsStopped) return;

    if(!timeIsStopped) timeIsStopped = true;
    else if(elapsed >= 72.0f) timeIsStopped = false;
}
