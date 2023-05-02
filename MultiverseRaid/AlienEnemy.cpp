#include "MultiverseRaid.h"
#include "AlienEnemy.h"
#include "Random.h"

EntityAttributes AlienEnemy::aliensAttributes = {
    6.0f, //hp
    440.0f, //speed
    7.0f, //damage
    3.5f, //attackSpeed
    0.30f, //defense
    30.0f //range
};

AlienEnemy::AlienEnemy(): hp(aliensAttributes.hp) {
    sprite = new Sprite("Resources/AlienEnemy.png");
    speed  = new Vector(0, 1.0f);
    BBox(new Circle(20.0f));

    Player * player = MultiverseRaid::player;
    speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
    RotateTo(-speed->Angle());
    
    RandF pos{ 100, 150 };
    MoveTo(pos.Rand(), pos.Rand());

    type = ALIEN_ENEMY;
}

AlienEnemy::~AlienEnemy() {
    delete sprite;
    delete speed;
    delete attackSpeedTimer;
}

void AlienEnemy::UpdateWaveAttributes() {
    aliensAttributes.hp += 3.0f;
    aliensAttributes.speed += 20.0f;
    aliensAttributes.damage += 2.0f;
    aliensAttributes.attackSpeed -= 0.2f;

    if(aliensAttributes.attackSpeed < 1.5f) {
        aliensAttributes.attackSpeed = 1.5f;
    }
}

void AlienEnemy::OnCollision(Object * obj) {
    if (obj->Type() != PLAYER) return;
    Player * player = MultiverseRaid::player;

    bool isFirstPlayerCollision = attackSpeedTimer == nullptr;
    if(isFirstPlayerCollision) {
        player->ApplyDamage(aliensAttributes.damage);
        attackSpeedTimer = new Timer();
        attackSpeedTimer->Start();

        return;
    }

    bool attackOnCooldown = attackSpeedTimer->Elapsed() < aliensAttributes.attackSpeed;
    if(attackOnCooldown) return;

    player->ApplyDamage(aliensAttributes.damage);
    attackSpeedTimer->Start();
}

void AlienEnemy::Update() {
    float parsedSpeed = aliensAttributes.speed * gameTime;
    Translate(speed->XComponent() * parsedSpeed, -speed->YComponent() * parsedSpeed);

    if (x < 100 || y < 100 || x > game->Width() - 100 || y > game->Height() - 100) {
        Player * player = MultiverseRaid::player;

        speed->RotateTo(Line::Angle(Point(x, y), Point(player->X(), player->Y())));
        RotateTo(-speed->Angle());
    }
}

void AlienEnemy::Draw() {
    sprite->Draw(x, y, Layer::LOWER, scale, rotation);
}
