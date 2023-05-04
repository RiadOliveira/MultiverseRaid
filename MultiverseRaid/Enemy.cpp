#include "Enemy.h"
#include "MultiverseRaid.h"

Enemy::Enemy() {
}

Enemy::~Enemy() {
    delete sprite;
    delete speed;
    delete attackSpeedTimer;
    delete damageReceiverTimer;
}

void Enemy::HandlePlayerCollision(float enemyDamage, float enemyAttackSpeed) {
    Player * player = MultiverseRaid::player;

    bool isFirstPlayerCollision = attackSpeedTimer == nullptr;
    if(isFirstPlayerCollision) {
        player->ApplyDamage(enemyDamage);
        attackSpeedTimer = new Timer();
        attackSpeedTimer->Start();

        return;
    }

    bool attackOnCooldown = attackSpeedTimer->Elapsed() < enemyAttackSpeed;
    if(attackOnCooldown) return;

    player->ApplyDamage(enemyDamage);
    attackSpeedTimer->Start();
}

void Enemy::HandlePlayerAttackCollision(
    PlayerAttack* attack, float damageReduction
) {
    float damageToApply = attack->DamagePerTick() * (1.0f - damageReduction);

    if(damageReceiverTimer == nullptr) {
        ApplyDamage(damageToApply);
        damageReceiverTimer = new Timer();
        damageReceiverTimer->Start();

        return;
    }

    if(damageReceiverTimer->Elapsed() >= attack->DamageTickTime()) {
        ApplyDamage(damageToApply);
        damageReceiverTimer->Reset();
    }
}