#include "Enemy.h"
#include "WizardAvatar.h"
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

void Enemy::HandleEntityCollision(Object* entity, float speed) {
    if(WizardAvatar::timeIsStopped) return;

    float angle = Line::Angle(Point(x, y), Point(entity->X(), entity->Y()));
    Vector vector = Vector(angle + 180.0f, speed);
    Translate(vector.XComponent() * gameTime, -vector.YComponent() * gameTime);

    if (x < 50) MoveTo(50, y);
    else if (x > game->Width() - 50) MoveTo(game->Width() - 50, y);

    if (y < 50) MoveTo(x, 50);
    else if (y > game->Height() - 50) MoveTo(x, game->Height() - 50);
}

void Enemy::HandlePlayerCollisionAttack(
    float enemyDamage, float enemyAttackSpeed, uint soundId
) {
    Player * player = MultiverseRaid::player;

    if(attackSpeedTimer->Elapsed() < enemyAttackSpeed) return;
    player->ApplyDamage(enemyDamage, enemyType);

    MultiverseRaid::audio->Play(soundId);
    attackSpeedTimer->Reset();
}

void Enemy::HandlePlayerAttackCollision(
    Attack* attack, float damageReduction
) {
    bool sameAsLastAttack = attack == lastAttackReceived;
    if(sameAsLastAttack && damageReceiverTimer->Elapsed() < attack->DamageTickTime()) return;

    float damageToApply = attack->DamagePerTick() * (1.0f - damageReduction);
    ApplyDamage(damageToApply);
    
    lastAttackReceived = attack;
    damageReceiverTimer->Reset();

    if(colorTimer == nullptr) {
        colorTimer = new Timer();
        colorTimer->Start();
    } else colorTimer->Reset();
}