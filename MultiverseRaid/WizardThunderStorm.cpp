#include "WizardThunderStorm.h"
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
}

WizardThunderStorm::~WizardThunderStorm() {
    delete cooldownTimer;
}

void WizardThunderStorm::OnCollision(Object* obj) {
    if(obj->Type() != ENEMY) return;
    if(cooldownTimer->Elapsed() < 3.0f) return;

    Point* target = new Point(obj->X(), obj->Y());
    MultiverseRaid::scene->Add(
        new ThunderStormLighting(target), MOVING
    );

    cooldownTimer->Reset();
    delete target;
}

void WizardThunderStorm::Update() {
    Player* player = MultiverseRaid::player;
    MoveTo(player->X(), player->Y());
}

void WizardThunderStorm::Draw() {
}