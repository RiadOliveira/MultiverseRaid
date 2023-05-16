#include "WizardThunderStorm.h"
#include "WizardAvatar.h"
#include "ThunderStormLighting.h"
#include "MultiverseRaid.h"
#include "Vector.h"

WizardThunderStorm::WizardThunderStorm() {
    Player* player = MultiverseRaid::player;
    if(player == nullptr) {
        MoveTo(game->CenterX() - 48.0f, game->CenterY() - 24.0f);
    } else MoveTo(player->X(), player->Y());
    
    cooldownTimer = new Timer();
    cooldownTimer->Start();
    BBox(new Circle(240.0f));

    type = PLAYER_PASSIVE;
}

WizardThunderStorm::~WizardThunderStorm() {
    delete cooldownTimer;
    MultiverseRaid::audio->Stop(THUNDER_STORM_LIGHTING);
}

void WizardThunderStorm::OnCollision(Object* obj) {
    if(obj->Type() != ENEMY) return;

    float attackSpeed = MultiverseRaid::player->Attributes().attackSpeed;
    float cooldown = 3.0f - (1.0f - attackSpeed);
    float legendaryModeModifier = 1.0f + (float) WizardAvatar::legendaryMode;

    float requiredElapsed = cooldown / legendaryModeModifier;
    if(cooldownTimer->Elapsed() < requiredElapsed) return;

    Point* target = new Point(obj->X(), obj->Y());
    MultiverseRaid::scene->Add(
        new ThunderStormLighting(target), STATIC
    );
    MultiverseRaid::audio->Play(THUNDER_STORM_LIGHTING);

    cooldownTimer->Reset();
    delete target;
}

void WizardThunderStorm::Update() {
    Player* player = MultiverseRaid::player;
    MoveTo(player->X(), player->Y());
}

void WizardThunderStorm::Draw() {
}