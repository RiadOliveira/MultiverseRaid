#include "MultiverseRaid.h"
#include "AlienEnemy.h"
#include "Random.h"

EntityAttributes AlienEnemy::defaultAttributes = {
    6.0f, //hp
    7.0f, //damage
    440.0f, //speed
    3.5f, //attackSpeed
    0.30f, //defense
    30.0f //range
};

EntityAttributes AlienEnemy::aliensAttributes = {
    6.0f, //hp
    7.0f, //damage
    440.0f, //speed
    3.5f, //attackSpeed
    0.30f, //defense
    30.0f //range
};

AlienEnemy::AlienEnemy() {
    speed  = new Vector(0, 1.0f);
    hp = aliensAttributes.hp;

    tileSet = new TileSet(
        "Resources/Alien/AlienEnemy.png",
        (uint)46, (uint)36, 1, 1
    );
    animation = new Animation(tileSet, 0.2f, true);
    uint sequence[1] = { 0 };
    animation->Add(0, sequence, 1);

    BBox(new Rect(-18.0f, -18.0f, 18.0f, 18.0f));
    Player * player = MultiverseRaid::player;
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    RotateTo(-speed->Angle());
    
    type = ENEMY;
    enemyType = ALIEN;
    MultiverseRaid::remainingEnemies++;
}

AlienEnemy::~AlienEnemy() {
    MultiverseRaid::remainingEnemies--;
}

void AlienEnemy::ResetWaveAttributes() {
    aliensAttributes.hp = defaultAttributes.hp;
    aliensAttributes.damage = defaultAttributes.damage;
    aliensAttributes.speed = defaultAttributes.speed;
    aliensAttributes.attackSpeed = defaultAttributes.attackSpeed;
    aliensAttributes.defense = defaultAttributes.defense;
    aliensAttributes.range = defaultAttributes.range;
}

void AlienEnemy::UpdateWaveAttributes() {
    aliensAttributes.hp += 3.0f;
    aliensAttributes.damage += 2.0f;
    aliensAttributes.speed += 20.0f;
    aliensAttributes.attackSpeed -= 0.2f;

    if(aliensAttributes.attackSpeed < 1.5f) {
        aliensAttributes.attackSpeed = 1.5f;
    }
}

void AlienEnemy::OnCollision(Object * obj) {
    if(obj->Type() == PLAYER) {
        HandlePlayerCollision(
            aliensAttributes.damage,
            aliensAttributes.attackSpeed
        );
        return;
    };
    if(obj->Type() != PLAYER_ATTACK) return;

    PlayerAttack* attack = (PlayerAttack*) obj;
    bool receiveIncreaseDamage = attack->DamageType() == ROBOT;
    float damageReduction = receiveIncreaseDamage ? 0.0f : aliensAttributes.defense;

    HandlePlayerAttackCollision(attack, damageReduction);
}

void AlienEnemy::Update() {
    animation->NextFrame();
    if(IsDead()) {
        MultiverseRaid::scene->Delete();
        return;
    }

    float parsedSpeed = aliensAttributes.speed * gameTime;
    Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);

    if (x < 100 || y < 100 || x > game->Width() - 100 || y > game->Height() - 100) {
        Player * player = MultiverseRaid::player;

        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        RotateTo(-speed->Angle());
    }
}
