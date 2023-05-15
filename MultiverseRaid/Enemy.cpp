#include "Enemy.h"
#include "MultiverseRaid.h"

Enemy::Enemy(): damageReceiverTimer(new Timer()), attackSpeedTimer(new Timer()) {
    damageReceiverTimer->Start();
    attackSpeedTimer->Start();
}

Enemy::~Enemy() {
    delete tileSet;
    delete animation;
    delete speed;
    delete attackSpeedTimer;
    delete damageReceiverTimer;
    delete colorTimer;
}

void Enemy::HandlePlayerCollision(float enemyDamage, float enemyAttackSpeed) {
    Player * player = MultiverseRaid::player;

    if(attackSpeedTimer->Elapsed() < enemyAttackSpeed) return;
    player->ApplyDamage(enemyDamage);
    attackSpeedTimer->Reset();
}

void Enemy::HandlePlayerAttackCollision(
    Attack* attack, float damageReduction
) {
    if(damageReceiverTimer->Elapsed() < attack->DamageTickTime()) return;

    float damageToApply = attack->DamagePerTick() * (1.0f - damageReduction);
    ApplyDamage(damageToApply);
    damageReceiverTimer->Reset();

    if(colorTimer == nullptr) {
        colorTimer = new Timer();
        colorTimer->Start();
    } else colorTimer->Reset();
}