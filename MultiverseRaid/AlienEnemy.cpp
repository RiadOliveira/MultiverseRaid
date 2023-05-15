#include "MultiverseRaid.h"
#include "AlienEnemy.h"
#include "Random.h"

EntityAttributes AlienEnemy::defaultAttributes = {
    6.0f, //hp
    7.0f, //damage
    440.0f, //speed
    2.0f, //attackSpeed
    0.30f, //defense
    30.0f //range
};

EntityAttributes AlienEnemy::aliensAttributes = {
    6.0f, //hp
    7.0f, //damage
    440.0f, //speed
    2.0f, //attackSpeed
    0.30f, //defense
    30.0f //range
};

AlienEnemy::AlienEnemy() {
    speed  = new Vector(0, 1.0f);
    hp = aliensAttributes.hp;

    tileSet = new TileSet(
        "Resources/Alien/AlienEnemy.png",
        (uint)300, (uint)200, 2, 4
    );
    animation = new Animation(tileSet, 0.2f, true);
    uint sequence[4] = { 0, 1, 2, 3 };
    animation->Add(0, sequence, 4);

    Point vertex[14] =
    {
        Point(6, -30), Point(24, -16), Point(24, -20),   Point(45, -1),
        Point(24, 20), Point(24, 16),  Point(6, 30),
        Point(-27, 30), Point(-16, 20), Point(-40, 16),
        Point(-45, -1), Point(-40, -16), Point(-16, -20), Point(-27, -30)

    };
    BBox(new Poly(vertex, 14));

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

    Attack* attack = (Attack*) obj;
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
