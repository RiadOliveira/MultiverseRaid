#include "Attack.h"
#include "MultiverseRaid.h"

Attack::Attack() {
    MoveTo(x, y, Layer::BACK);
}

Attack::~Attack() {
}

void Attack::SetDamageTickTime(float tickTime) {
    damageTickTime = tickTime;
}

void Attack::SetDamagePerTick(float damage) {
    damagePerTick = damage;

    if(type == PLAYER_ATTACK) {
        float damage = MultiverseRaid::player->Attributes().damage;
        damagePerTick += damage;
    }
}
